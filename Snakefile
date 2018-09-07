rule qc:
    input:
        "reads/testbestand1.fastq",
        "reads/testbestand2.fastq"
    output:
        "qc_output/test.qc"
    shell:
        'bash qc.sh {input} > {output}'
