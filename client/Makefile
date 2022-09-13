COMPILE=javac
RUN=java
OUT_FOLDER=./classes/
SRC_FOLDER=./src/

init: clean
	$(COMPILE) -d $(OUT_FOLDER) $(SRC_FOLDER)*.java

clean:
	rm -rf $(OUT_FOLDER)*

run:	
	cd $(OUT_FOLDER) && $(RUN) Main 127.0.0.1 6666
