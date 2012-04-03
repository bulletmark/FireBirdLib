JB = JailBreak

all: ${JB}

${JB}: ${JB}.c
	gcc -o $@ $<

.PHONY: doc

doc:
	markdown README.md >README.html

clean:
	rm -f JailBreak README.html
