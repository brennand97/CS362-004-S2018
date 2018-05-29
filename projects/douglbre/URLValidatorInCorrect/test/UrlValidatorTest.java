

import org.junit.Test;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   @Test
   public void testManualTest()
   {
	   
	   // You can use this function to implement your manual testing
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   // Pass
	   
	   assertTrue(urlVal.isValid("ftp://www.google.com")); 
	   // Bug #1 Found (fix this and then run the program again)
	   //		Failure: java throws ExceptionIninitializerError
	   //	    Fix: change “regexs != null” to “regexs == null” on line 120 of RegexValidator.java
	   // Bug #2 Found (fix this and then run the program again)
	   //		Failure: java throws NullPointerException
	   //	    Fix: change “regexs.length-1” to “regexs.length” on line 125 of RegexValidator.java
	   // Bug #3 Found (fix this and then run the program again)
	   //		Failure: java throws NullPointerException
	   //	    Fix: change “return null” to “return VALIDATOR” on line 68 of InetAddressValidator.java
	   // Bug #4 Found (fix this and then run the program again)
	   //		Failure: java throws NullPointerException
	   //	    Fix: change “groups != null” to “groups == null” on line 88 of InetAddressValidator.java
	   // Bug #5 Found (fix this and then run the program again)
	   //		Failure: junit throws AssertionFailedError
	   //	    Fix: change “!isValidTld(groups[0])” to “isValidTld(groups[0])” on line 166 of DomainValidator.java
	   
	   assertTrue(urlVal.isValid("file:")); 
	   // Bug #6 Found (fix this and then run the program again)
	   //		Failure: junit throws AssertionFailedError
	   //	    Fix: change “http” to “file” on line 318 of UrlValidator.java
	   
	   // Manual tests for using custom schemes
	   String customSchemes[] = {"abc","123"};
	   UrlValidator urlValCustomSchemes = new UrlValidator(customSchemes);
	   
	   assertFalse(urlValCustomSchemes.isValid("http://www.google.com")); 
	   // Pass
	   
	   assertTrue(urlValCustomSchemes.isValid("abc://www.google.com"));
	   // Bug #7 Found (fix this and then run the program again)
	   //		Failure: junit throws AssertionFailedError
	   //	    Fix: change “toUpperCase” to “toLowerCase” on line 282 of UrlValidator.java
	   
	   assertFalse(urlValCustomSchemes.isValid("123://www.google.com")); 
	   // Pass
   }
   
   @Test
   public void testYourFirstPartition()
   {
	   // You can use this function to implement your First Partition testing

	   UrlValidator urlVal = new UrlValidator();

	   // Tests covering the partitions and boundaries for IPv4 Addresses

	   assertFalse(urlVal.isValid("ftp://-1.-1.-1.-1"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://0.0.0.0"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://128.128.128.128"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://255.255.255.255"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://256.256.256.256"));
	   // Bug #8 Found (fix this and then run the program again)
	   //		Failure: junit throws AssertionFailedError
	   //		Fix: change “return true” to “return false” on line 107 of InetAddressValidator.java

	   // Special cases to test for IPv4 addresses

	   assertFalse(urlVal.isValid("ftp://"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://."));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://0."));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://...."));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://0...."));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://0.0."));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://0.0.0.0."));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://0.0.0."));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://0.0"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://0"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://0000"));
	   // Pass

   }
   
   @Test
   public void testYourSecondPartition(){
	// You can use this function to implement your Second Partition testing

	   UrlValidator urlVal = new UrlValidator();

	   // Tests covering the partitions for a path
	   assertTrue(urlVal.isValid("ftp://www.google.com/a"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/A"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/0"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/~"));
	   // Bug #9 (first portion) Found (fix this and then run the program again)
	   //		Failure: junit throws AssertionFailedError
	   //		Fix: change “^(/[-\\w:@&?=+,.!*'%$_;\\(\\)]*)?$” to “^(/[-\\w:@&?=+,.!*'%$_;\\(\\)~]*)?$” on line 167 of UrlValidator.java

	   assertTrue(urlVal.isValid("ftp://www.google.com/!"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/@"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/#"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/$"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/%"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/^"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/&"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/*"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/("));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/)"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/-"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/_"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/="));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/+"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/["));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/{"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/]"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/}"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/\\")); // "\\" is one back-slash character
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/|"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/;"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/:"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/'"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/\""));  // "\"" is one double-quote character
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/,"));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/<"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/."));
	   // Pass

	   assertFalse(urlVal.isValid("ftp://www.google.com/>"));
	   // Pass

	   assertTrue(urlVal.isValid("ftp://www.google.com/a/")); // separator character needed between the two slashes because we are not using the ALLOW_2_SLASHES option
	   // Bug #9 (second portion) Found (fix this and then run the program again)
	   //		Failure: junit throws AssertionFailedError
	   //		Fix: change “^(/[-\\w:@&?=+,.!*'%$_;\\(\\)~]*)?$” to “^(/[-\\w:@&?=+,.!*'%$_;\\(\\)~/]*)?$” on line 167 of UrlValidator.java

	   assertTrue(urlVal.isValid("ftp://www.google.com/?"));
	   // Pass

   }
   //You need to create more test cases for your Partitions if you need to 
   
   @Test
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
