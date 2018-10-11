rule qc:
    input:
        "reads/testbestand1.fastq",
        "reads/testbestand2.fastq"
    output:
        "qc_output/test.qc"
    shell:
        'bash qc.sh {input} > {output}'

rule trim:
    input:
        "reads/testbestand1.fastq",
        "reads/testbestand2.fastq"
    output:
        "trim_output/test1.trim",
        "trim_output/test2.trim"
    shell:
        './trim {input} {output}'
