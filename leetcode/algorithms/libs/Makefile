JAVA := java
JAVAC := javac
JAVACFLAGS := -Xlint:all

.SUFFIXES: .java .class
.java.class:
	$(JAVAC) $(JAVACFLAGS) $*.java

CLASSES = $(wildcard *.java)

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
