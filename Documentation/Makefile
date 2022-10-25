FILES = src/*.md
OUTPUT = build/report.pdf
PANDOC = pandoc

FLAGS = --bibliography=./lib/bibliography.bib \
		--from=markdown \
		--to=latex \
		--filter=pandoc-crossref \
		--citeproc \
		--toc \
		--highlight-style=tango \
		--metadata-file=metadata.yaml \
		-s \
		-t pdf

all: $(OUTPUT)

$(OUTPUT): $(FILES)
	$(PANDOC) $(FLAGS) -o $(OUTPUT) $(FILES)

clean:
	rm -f $(OUTPUT)
