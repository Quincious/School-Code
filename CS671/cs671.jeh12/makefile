# specify sources for each assignment here
SOURCES1 := Guesser.java Liar.java HiLo.java GuesserTextUI.java
SOURCES2 := Tester.java Testable.java TestMethod.java TestResult.java
SOURCES3 := Future.java Callable.java Callback.java CompletedFuture.java Continue.java Executor.java FactoryExecutor.java FailedFuture.java MyFuture.java NotExecutedException.java
SOURCES4 := pig/Coin.java pig/Competition.java pig/Die.java pig/Strategy.java pig/UserTerminalStrategy.java pig/Utils.java pig/server/MatchMaker.java pig/server/Message.java pig/server/ProtocolToStrategy.java pig/server/StrategyToProtocol.java pig/server/TerminalClient.java

################################################################################

JAVAC := javac -sourcepath src -Xlint -d .
.PHONY: clean all 1 2 3 4

vpath %.java src/cs671

all: 1 2 3 4 html tests

tests: cs671 src/tests/*.java
	$(JAVAC) src/tests/*.java
	@touch tests

html: $(SOURCES1) $(SOURCES2) $(SOURCES3) $(SOURCES4)
	javadoc @javadoc-options cs671
	@touch html

clean:
	/bin/rm -rf cs671 html tests

1: SOURCES := $(addprefix src/cs671/,$(SOURCES1))
2: SOURCES := $(addprefix src/cs671/,$(SOURCES2))
3: SOURCES := $(addprefix src/cs671/,$(SOURCES3))
4: SOURCES := $(addprefix src/cs671/,$(SOURCES4))

cs671: $(SOURCES1) $(SOURCES2) $(SOURCES3) $(SOURCES4)
	$(JAVAC) $(SOURCES)
	@touch cs671

1: cs671
2: cs671
3: cs671
4: cs671
