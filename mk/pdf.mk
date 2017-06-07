# ======================================================================
# pdf.mk
# ======================================================================

PDFLATEX = pdflatex -file-line-error -halt-on-error -synctex=1
BIBTEX = biber
PS2EPS = ps2pdf14
MAKEINDEX = makeindex -L


FIGURES ?= diamondrule
EFIGURES = $(addsuffix .eps, $(FIGURES))
PFIGURES = $(addsuffix .pdf, $(FIGURES))

ARTICLE_NAME ?= $(shell basename $$(pwd))
PDF_NAME = $(ARTICLE_NAME).pdf
ARTICLE_TEX = $(ARTICLE_NAME).tex

deps = $(shell find . -name "*.tex") $(shell find . -name "*.cls") $(shell find . -name "*.bib")

bad_extensions = aux bbl bcf blg fdb_latexmk fls gz \
					idx ilg ind log out pdf run.xml toc

all: $(PDF_NAME)


$(PFIGURES): %.pdf:%.eps
	$(PS2EPS) $<

$(PDF_NAME): $(deps) $(PFIGURES)
	$(PDFLATEX) $(ARTICLE_TEX)
	$(MAKEINDEX) $(ARTICLE_NAME).idx
	$(PDFLATEX) $(ARTICLE_TEX)
	$(PDFLATEX) $(ARTICLE_TEX)
	$(PDFLATEX) $(ARTICLE_TEX)

clean:
	for extension in $(bad_extensions); do \
		rm -f $$(find . -name "*.$$extension"); \
	done;

.PHONY: all clean
