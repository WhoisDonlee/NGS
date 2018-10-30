rule qc:
    input:
        "reads/testbestand1.fastq",
        "reads/testbestand2.fastq"
    output:
        "output_qc/test1.qc",
        "output_qc/test2.qc"
    shell:
        './qc.out {input} {output}'

rule trim:
    input:
        "reads/testbestand1.fastq",
        "reads/testbestand2.fastq"
    output:
        "output_trim/test1.trim",
        "output_trim/test2.trim"
    shell:
        './trim.out {input} {output}'
