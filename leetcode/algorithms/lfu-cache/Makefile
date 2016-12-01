JAVA := java
JAVAC := javac
JAVACFLAGS := -Xlint:all

default: clean build run

build:
	$(JAVAC) $(JAVACFLAGS) *.java

clean:
	$(RM) *.class

run:
	$(JAVA) LFUCache
