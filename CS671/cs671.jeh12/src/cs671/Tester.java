// $Id: Tester.java 232 2014-01-27 02:40:06Z cs671a $

package cs671;

import java.lang.annotation.Annotation;
import java.lang.reflect.*;
import java.util.*;
import java.io.*;

/** Test runner.  This class is used to run the tests methods
 * (annotated with {@code @TestMethod}) found in classes that
 * implement {@code Testable}.
 * 
 * <p>Instances of this class exist in two flavors, whether they run a
 * single test class (see {@code makeTester}) or a suite of test
 * classes (see {@code makeSuite}).  Suites can be nested.  They
 * cannot be empty.  All the test classes (or sub-suites) in a suite
 * are processed in order.  All the test methods in a test class are
 * invoked in string order of their names.  Furthermore, they are all
 * invoked on the same instance.
 *
 * <p>Test classes have type {@code Testable}. A {@code beforeMethod}
 * is run before each test method.  If this method returns {@code
 * false} (or fails), the corresponding test is not run.  An {@code
 * afterMethod} is run after each test, whether the test was
 * successful or not.  It is not run of the test was not run.
 * Failures in the {@code afterMethod} are reported as warnings but
 * have no further effect.
 *
 *<p>In general, no-argument methods are valid test methods if they
 * are annotated, even when they are non-public or non-void.  Static
 * method and methods that require arguments are ignored.  A warning
 * is displayed if they are test-annotated.
 *
 * <p>Tests results are produced as immutable {@code TestResult}
 * instances.  No pass/fail report is generated.  I/O is used to
 * report problems with test classes (which are disctinct from failed
 * tests), including incorrectly annotated methods, classes that fail
 * to load, classes that cannot be instantiated, etc.  These are
 * reported either as ERRORS (no tests are run) or as WARNINGS (some
 * tests are run).  By default, errors and warnings go to {@code
 * System.err} but they can be redirected or even ignored (see {@code
 * setPrintWriter}).
 *
 * <p>A tester can only been run once (whether directly or as part of
 * a suite).  Any attempt to run it again will result in a {@code
 * IllegalStateException},
 *
 * <p>Instances of this class are <em>not</em> safe for multi-threading.
 *
 * @author  Michel Charpentier
 * @version 2.0, 01/26/14
 * @see TestMethod
 * @see Testable
 */
public abstract class Tester implements Runnable {

	/**
	 * class flags and variables
	 */
	boolean hasRun = false;//flag to determine if tester has been run	
	PrintWriter output = new PrintWriter(new OutputStreamWriter(System.err), true);//Output Stream for test results, defaults to System.err
		
	/**
	* class collections
	*/
	List<Class<? extends Testable>> classesToTest = new ArrayList<Class<? extends Testable>>();//classes the tester will test
	List<TestResult> testResults = new ArrayList<TestResult>();//container for results of tests
	
	List<Testable> objects = new ArrayList<Testable>();
	
	/** Package-private constructor. */
	Tester () {}
	
	/** Sets the tester output.  By default, the output is {@code
	* System.err}.  It is valid to set the output to {@code null}, in
	* which case the tester is completely silent.
	*
	* @param w the output for tester info; can be {@code null}
	*/
	public abstract void setPrintWriter (PrintWriter w);
	
	/** Runs all the tests in the test class or suite.
	 * @throws IllegalStateException if this tester has already been run.
	 */
	public abstract void run ();
	
	/** Test results.  This method returns a list that contains a {@code
	 * TestResult} object for each test that was run (in the order the
	 * test method were actually run).  The returned list can be
	 * modified and modifications have no affect on this tester (i.e.,
	 * this method make a copy of the list of results)
	 *
	 * @throws IllegalStateException if the tester has not yet been run
	 */
	public abstract List<TestResult> getResults ();
	
	/** Starts a console-based application.  Command line arguments are
	 * the names of the classes to be tested.  The application produces
	 * a summary output of tests that succeeded and tests that failed.
	 */
		
	
	/** 
	 * class for this instance of Tester.
	 */
	static class MyTester extends Tester{
				
		/**
		 * 
		 * creates a tester for the given classes
		 */
		 @SuppressWarnings("unchecked")
		public MyTester(Class<? extends Testable>... classes){

			for (Class<? extends Testable> curClass : classes)
		      this.classesToTest.add(curClass);

		  }
		  /**
		*Creates a tester for the given collection of classes
		*/
		  public MyTester(Collection<Class<? extends Testable>> classes){
		    
			  for (Class<? extends Testable> curClass : classes)				  
				  this.classesToTest.add(curClass);
		    
		  }
		
		
		@Override
		public void setPrintWriter(PrintWriter w) {
			//This info was taken from:
			//stackoverflow.com/questions/691813/is-there-a-null-outputstream-in-java
		    class NullOutputStream extends OutputStream {
		    	
		      @Override
		      public void write(int b) throws IOException {}
		    }
		    
		    if(w == null){
		    	
		      this.output = new PrintWriter(new NullOutputStream());
		      
		    }else{
		    	
		      this.output = w;
		      
		    }
			
		}

		@Override
		public void run() {
			
			if(hasRun){
				throw new IllegalStateException();
			}
			
			for (Class<? extends Testable> curClass : classesToTest) {
				
				// collection for tests of this class
				List<MyTestResult> tests = new ArrayList<MyTestResult>();
				
				// temp object for testing
				Testable tempTestable = null;
				
				// get methods for testing
				List<Method> tempMethods = new ArrayList<Method>(Arrays.asList(curClass.getDeclaredMethods()));
				List<Method> methods = new ArrayList<Method>();
				
				try {
					
					// try to initialize
					Constructor<? extends Testable> constructor = curClass.getDeclaredConstructor();
					//set accessible to true
					constructor.setAccessible(true);
					
					//get instance of constructor
					tempTestable = constructor.newInstance();
					
				} catch (Error ex) {

					output.println("ERROR "+ curClass.toString() + " UnknownError");

				} catch (Exception ex) {

					output.println("ERROR "+ curClass.toString() + " UnknownError");

				}

                //if no methods, go to next class
				if (tempMethods.isEmpty()) {
					
					output.println("ERROR: No methods found to test in class "+ curClass.getName() + "");
					continue;
				}
				
				//get names of methods for sorting alphabetically
				List<String> names = new ArrayList<String>();
				
				for (Method method : tempMethods) {
					
					names.add(method.getName());
					
				}
				
				//sort list of names
				Collections.sort(names);
				
				//fill methods collection with alphabetized list
				for (String name : names) {
					
					for (Method method : tempMethods) {
						
						if (name.matches(method.getName())) {
						
							methods.add(method);
							break;
						}
					}
				}
				
				for (Method method : methods) {
					
					// Test if method is applicable for testing,(ie. not static,
					// no parameters and can be invoked)
					try {
						
						method.setAccessible(true);
						
					} catch (SecurityException ex) {
						
						output.println("ERROR: Security prevents you from running your tests.");
						return;
						
					}
					
					if (!method.isAnnotationPresent(TestMethod.class)) {
						// test if method is annotated w/test
						continue;
						
					} else {
						
						try {
							// try to get annotation parameters
							TestMethod annotation = method.getAnnotation(TestMethod.class);
							
						
							ArrayList<Field> fields = new ArrayList<Field>(Arrays.asList(method.getClass().getDeclaredFields()));
							
							for (Field field : fields)								
								field.setAccessible(true);
													
							assert (annotation.info() instanceof String);
							
							tests.add(new MyTestResult(method, annotation.weight(), annotation.info(), curClass));
							
						} catch (IllegalArgumentException ex) {

							output.println("ERROR: " + method.getName() + " in class " + curClass.getName() + " : " + ex.toString() + " raised");
						} catch (NullPointerException ex) {

							output.println("ERROR: " + method.getName() + " in class " + curClass.getName() + " : " + ex.toString() + " raised");
						} catch (ClassCastException ex) {

							output.println("ERROR: " + method.getName() + " in class " + curClass.getName() + " : " + ex.toString() + " raised");
						}
                    }
				}
				
				for (MyTestResult testResult : tests) {
					
					// Run the tests
					if (testResult.getWeight() <= 0) {
					
						continue;
						
					}
					
					try {
						
						// invoke beforeMethod
						boolean check = tempTestable.beforeMethod(testResult.method);
						
						if (!check)
						{
							output.println("WARNING: beforeMethod(" + testResult.method.getName() + ") is false; test not run");
							continue;
						}
													
						
					} catch (Exception ex) {
						
						output.println("WARNING: beforeMethod(" + testResult.method.getName() + ") failed; " + ex.toString());
						continue;
					}
					
					if (testResult.method.getParameterTypes().length != 0) {
						
						// test if method takes parameters
						output.println("WARNING: method " + testResult.method.getName() + " is annotated with @Test but takes parameters; ignored");
						continue;
						
					} else if (Modifier.isStatic(testResult.method.getModifiers())) {
						
						// test if method is static
						output.println("WARNING: " + testResult.method.getName() + " is static; ignored");
						continue;
						
					}
					try {
						
						// invoke method
						testResult.duration = System.nanoTime()/Math.pow(10,9);
						testResult.method.invoke(tempTestable);
						testResult.duration = System.nanoTime()/Math.pow(10,9) - testResult.duration;
						testResult.success = true;
						
					} catch (InvocationTargetException err) {
						
						Throwable ex = err.getTargetException();
						testResult.duration = System.nanoTime()/Math.pow(10,9) - testResult.duration;
						testResult.error = ex;
						
					} catch (Exception ex) {
						
						testResult.duration = System.nanoTime()/Math.pow(10,9) - testResult.duration;
						testResult.error = ex;
						
					}
					try {
						
						// invoke afterMethod
						tempTestable.afterMethod(testResult.method);
						output.println("afterMethod no catch");
						
					} catch (Error ex) {

						output.println("WARNING:After Method for" + testResult.method.getName() + " method %s has failed");
					} catch (Exception ex) {

						output.println("WARNING:After Method for" + testResult.method.getName() + " method %s has failed");
					}

                    this.testResults.add(testResult);
				}
			}
			
			hasRun = true;			
		}

		@Override
		public List<TestResult> getResults() {
			
			if (!hasRun) {

				throw new IllegalStateException();
			}
			
			return testResults;
		}
		
	}

	/**
	*This implementation's version of the TestResult interface.
	*Contains all fields & methods from that interface as well as
	*holding the method the test result is for and the class it is from
	*/
	class MyTestResult implements TestResult {
		
		/**
		 * Class variables
		 */
		Method method;//method being tested
		Class<? extends Testable> _class;//class of method
		double weight;//weight of test
		String info;//info string of method				
		boolean success;//success flag of test
		double duration;//time of test
		Object returned;//return value of method
		Throwable error;//error thrown		
		String name;

		/**
		 * Initalizes this test result
		 * 
		 * @param method - The method that is being tested
		 * @param weight - The weight of this test
		 * @param info - The info string of the method
		 * @param _class - The class the method is in
		 */
		MyTestResult(Method method, double weight, String info,
				Class<? extends Testable> _class) {
				
				
			this.method = method;
			this.weight = weight;
			this.info = info.equals("") ? info : ": " + info;
			this.success = false;
			this.duration = 0.0;
			this.error = null;
			this.returned = null;
			this._class = _class;
			this.name = _class.getCanonicalName() + "." + method.getName();
		}

		public double getWeight() {
			return weight;
		}

		public boolean success() {
			return success;
		}

		public String getInfo() {
			return name + info;
		}

		public double getDuration() {
			return duration;
		}

		public Throwable error() {
			return error;
		}
	}
	
	
	
	public static void main (String[] args) {
	  	  
		//list to hold classes to from args
		List<Class<? extends Testable>> argsClasses = new ArrayList<Class<? extends Testable>>();
	    
		//ensure there are args
		if(args.length <= 0){
			
			System.out.println("Must enter one or more classes as arguments");
			return;
		}
		
		ClassLoader cLoader = ClassLoader.getSystemClassLoader();
		
		//see if all args are loadable classes and testable
		for(String arg: args){
			
			try{
				
				Class<?> currentArg = cLoader.loadClass(arg);
				//ensure it extends Testable 
				Class<? extends Testable> curArgSubClass = currentArg.asSubclass(Testable.class);
				
				//add class to list
				argsClasses.add(curArgSubClass);	
				
			} catch(ClassCastException ex){
				//class not testable, print error then return
				System.out.println("class " + arg + " is not testable.");
				return;
				
			} catch (ClassNotFoundException e) {
				//class not loadable, print error then return
				System.out.println("class " + arg + " is not loadable");
				return;
				
			}			
		}
		
		assert(!argsClasses.isEmpty());
		
		List<MyTestResult> results = new ArrayList<MyTestResult>();
		
		List<Tester> testers = new ArrayList<Tester>();
		
		//create tester for each class
		for(Class<? extends Testable> argClass: argsClasses)
			testers.add(makeTester(argClass));
		
		//get main tester
		Tester testRun = makeSuite(testers);
		
		//run tester
		testRun.run();
		
		//get all results
		List<TestResult> tempResults = testRun.getResults();
		
		for(TestResult testResult: tempResults)
			results.add((MyTestResult)testResult);
		
		List<MyTestResult> successes = new ArrayList<MyTestResult>();
		List<MyTestResult> failures = new ArrayList<MyTestResult>();
		
		double score = 0;
		double total = 0;
		
		for(MyTestResult testResult: results){
			
			total += testResult.getWeight();
			
			if(testResult.success()){
				successes.add(testResult);
				score += testResult.getWeight();
			}
			else
				failures.add(testResult);
			
		}
		
	    System.out.println("SUCCESSFUL TESTS:");
		
		for(MyTestResult success: successes){
			
			System.out.println(" " + success.getInfo() + " "
					+ String.format("(%.1f)", success.getWeight()) + " in "
					+ String.format("%.5f", success.getDuration() * Math.pow(10, -3))
					+ " milliseconds");
		}
		
		System.out.println("FAILED TESTS:");
		for (MyTestResult fail : failures) {
			
			System.out.println(" " + fail.getInfo() + " "
					+ String.format("(%.1f)", fail.getWeight()) + " from "
					+ fail.error.toString());
			
		}
		
		System.out.println(String.format("SCORE = %.2f%%",(score/total)*100));
			
		return;
	}
	
	/** Creates a tester for a single test class.  This method only
	 * creates the tester.  It makes no attempt to load the class,
	 * instantiate it, look for test methods, etc.
	 */
	@SuppressWarnings("unchecked")
	public static Tester makeTester (Class<? extends Testable> tests) {
						
		return new MyTester(tests);
	}
	
	/** Creates a tester for a suite of testers. */
	public static Tester makeSuite (Tester... testers) {		
		
		List<Class<? extends Testable>> classes = new ArrayList<Class<? extends Testable>>();
		
		for (Tester curTester : testers){
			  
			for(Class<? extends Testable> curClass: curTester.classesToTest){
		    
				classes.add(curClass);
			}
		  }
		
		return new MyTester(classes);
	}
	
	/** Creates a tester for a suite of testers. */
	public static Tester makeSuite (List<? extends Tester> testers) {

		List<Class<? extends Testable>> classes = new ArrayList<Class<? extends Testable>>();
		
		for (Tester curTester : testers){
			  
			for(Class<? extends Testable> curClass: curTester.classesToTest){
		    
				classes.add(curClass);
			}
		  }
		
		return new MyTester(classes);
	}
	
	
	
}
