LIBS := ../libs
JAVA := java
JAVAC := javac
JAVACFLAGS := -Xlint:all

default: clean build run

build:
	make -C $(LIBS)
	mv $(LIBS)/*.class .
	$(JAVAC) $(JAVACFLAGS) *.java

clean:
	make -C $(LIBS) clean
	$(RM) *.class

run:
	$(JAVA) -ea Solution
