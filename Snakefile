#SAMPLES = ['bngsa_nietinfected']
SAMPLES = ['testbestand']

import os

docstring= r"""
    Dit is de BNEXTGEN Pipeline.
    """

if 'help' in config:
    print(docstring)
    os._exit(0)

rule all:
    input:
        expand('out_qc/{sample}_qc_1.fastq', sample=SAMPLES),
        expand('out_qc/{sample}_qc_2.fastq', sample=SAMPLES),
        expand('out_qc/{sample}_qctrimmed_1.fastq', sample=SAMPLES),
        expand('out_qc/{sample}_qctrimmed_2.fastq', sample=SAMPLES),
        expand('out_bowtie/{sample}.sorted.bam.bai', sample=SAMPLES),
        expand('refgen/infected_consensus.fasta.fai'),
        expand('out_bowtie/{sample}.bcf', sample=SAMPLES),
        expand('output/{sample}_consensus.fastq', sample=SAMPLES),

#rule symlink:
#    input:
#        genome = '/home/bnextgen/refgenome/infected_consensus.fasta',
#        #r1 = '/home/bnextgen/reads/{sample}_1.fastq',
#        #r2 = '/home/bnextgen/reads/{sample}_2.fastq'
#    output:
#        genome = 'refgen/infected_consensus.fasta',
#        #r1 = 'reads/{sample}_1.fastq',
#        #r2 = 'reads/{sample}_2.fastq',
#    run:
#        for i in range(len(input)):
#            os.system('ln -s '+input[i]+' '+output[i])

rule trim:
    input:
        r1 = 'reads/{sample}_1.fastq',
        r2 = 'reads/{sample}_2.fastq'
    output:
        r1 = 'out_trim/{sample}_trimmed_1.fastq',
        r2 = 'out_trim/{sample}_trimmed_2.fastq'
    shell:
        './trim.out {input} {output}'

rule qc:
    input:
        rules.trim.input
        #r1 = 'reads/{sample}_1.fastq',
        #r2 = 'reads/{sample}_2.fastq'
    output:
        r1 = 'out_qc/{sample}_qc_1.fastq', 
        r2 = 'out_qc/{sample}_qc_2.fastq'
    shell:
        './qc.out {input} {output}'

rule qcTrim:
    input:
        rules.trim.output
        #r1 = 'out_trim/{sample}_trimmed_1.fastq',
        #r2 = 'out_trim/{sample}_trimmed_2.fastq'
    output:
        r1 = 'out_qc/{sample}_qctrimmed_1.fastq', 
        r2 = 'out_qc/{sample}_qctrimmed_2.fastq'
    shell:
        './qc.out {input} {output}'

rule bt2build:
    input:
        genome = 'refgen/infected_consensus.fasta'
    params:
        refgen = 'infconsensus'
    output:
        'refgen/infconsensus.1.bt2',
        'refgen/infconsensus.2.bt2',
        'refgen/infconsensus.3.bt2',
        'refgen/infconsensus.4.bt2',
        'refgen/infconsensus.rev.1.bt2',
        'refgen/infconsensus.rev.2.bt2'
    shell:
        'bowtie2-build --threads 8 {input} refgen/{params.refgen}'

rule bowtie2:
    input:
        rules.bt2build.output,
        sample=["out_trim/{sample}_trimmed_1.fastq", "out_trim/{sample}_trimmed_2.fastq"]
    output:
        'out_bowtie/{sample}.bam'
    params:
        index='refgen/infconsensus',
        extra=""
    threads: 8
    wrapper:
        "0.37.1/bio/bowtie2/align"

# rule samtools_sort:
#     input:
#         rules.bowtie2.output,
#         #"out_bowtie/bngsa_nietinfected.bam"
#     output:
#         "out_bowtie/{sample}.sorted.bam"
#         #"out_bowtie/bngsa_nietinfected.sorted.bam"
#     shell:
#         "samtools sort -@ 8 {input} {output} && mv {output}.bam {output}"
rule samtools_sort:
    input:
        rules.bowtie2.output,
    output:
        "out_bowtie/{sample}.sorted.bam"
    params:
        "-m 4G"
    threads:  # Samtools takes additional threads through its option -@
        8     # This value - 1 will be sent to -@.
    wrapper:
        "0.37.1/bio/samtools/sort"

rule samtools_index:
    input: rules.samtools_sort.output,
    output: "out_bowtie/{sample}.sorted.bam.bai"
    params:
        "" # optional params string
    wrapper:
        "0.37.1/bio/samtools/index"

rule refgen_index:
    input: "refgen/infected_consensus.fasta"
    output: "refgen/infected_consensus.fasta.fai"
    # shell: "ln -s /home/bnextgen/refgenome/infected_consensus.fasta refgen/. && samtools faidx refgen/infected_consensus.fasta"
    shell: "samtools faidx refgen/infected_consensus.fasta"

rule samtools_mpileup:
    input: rules.samtools_sort.output,
    output: "out_bowtie/{sample}.bcf" # A pileup file
    shell: "samtools mpileup -uf refgen/infected_consensus.fasta {input} > {output}"
  
rule bcf_to_vcf:
    input:
        rules.samtools_mpileup.output
    output:
        "out_bowtie/{sample}.vcf"
    shell:
        # "bcftools view -cg {input} > {output}"
        "bcftools call -m {input} > {output}"

rule vcf2fq:
    input:
        rules.bcf_to_vcf.output
    output:
        "output/{sample}_consensus.fastq"
    shell:
        "/usr/share/samtools/vcfutils.pl vcf2fq {input} > {output}"

rule varcount:
    input:
        rules.bcf_to_vcf.output
    output:
        "result.txt"
    shell:
        "sh varcount.sh {input} > {output}"

