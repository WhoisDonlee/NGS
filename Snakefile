rule all:
    input:
        "output_qc/untrimmed1.qc",
        "output_qc/untrimmed2.qc",
        "output_qc/trimmed1.qc",
        "output_qc/trimmed2.qc"

rule qc:
    input:
        "reads/testbestand1.fastq",
        "reads/testbestand2.fastq"
    output:
        "output_qc/untrimmed1.qc",
        "output_qc/untrimmed2.qc"
    shell:
        './qc.out {input} {output}'

rule trim:
    input:
        "reads/testbestand1.fastq",
        "reads/testbestand2.fastq"
    output:
        "output_trim/trimmed1.fastq",
        "output_trim/trimmed2.fastq"
    shell:
        './trim.out {input} {output}'

rule qctrimmed:
    input:
        "output_trim/trimmed1.fastq",
        "output_trim/trimmed2.fastq"
    output:
        "output_qc/trimmed1.qc",
        "output_qc/trimmed2.qc"
    shell:
        './qc.out {input} {output}'

rule bowtie2build:
	input: 
		"/home/bnextgen/refgenome/infected_consensus.fasta"
	params:
		"/home/s1098137/output/reference"
	output:
		"/home/s1098137/output/reference.1.bt2",
		"/home/s1098137/output/reference.2.bt2",
		"/home/s1098137/output/reference.3.bt2",
		"/home/s1098137/output/reference.4.bt2",
		"/home/s1098137/output/reference.rev.1.bt2",
		"/home/s1098137/output/reference.rev.2.bt2"
	shell: 
		"bowtie2-build {input} {params}"

rule bowtie2:
    input:
        sample=["reads/testbestand1.fastq", "reads/testbestand2.fastq"]
    output:
        "mapped/infconsensus.bam"
    log:
        "logs/bowtie2/infconsensus.log"
    params:
        index="index/genome",  # prefix of reference genome index (built with bowtie2-build)
        extra=""  # optional parameters
    threads: 8
    wrapper:
        "0.27.1/bio/bowtie2/align"
