

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
	   assertTrue(urlVal.isValid("file:///anything/may/go/here/"));
	   // Pass
	   assertTrue(urlVal.isValid("file:///home/user/my/file/path/file.txt"));
	   // Pass
	   
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

UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String[] schemes = {
			   "http://",
			   "https://",
			   "htt:p//",
			   "ftp://",
			   "123://",
			   "://",
			   "//:"
	   };
	   
	   boolean[] schemesTrue = {
			   true,
			   true,
			   false,
			   true,
			   false,
			   false,
			   false
	   };
	   
	   String[] addresses = {
			   "www.google.com",
			   "google.com",
			   "asldkjf.com",
			   "laskdfj&*asdf.org",
			   "127.0.0.1",
			   "0.0.0.0",
			   "192.168.0255.0"
	   };
	   
	   boolean[] addressesTrue = {
			   true,
			   true,
			   true,
			   false,
			   true,
			   true,
			   false
	   };
	   
	   String[] ports = {
			   "",
			   ":80",
			   ":9090:",
			   ":80_90",
			   ":abc"
	   };
	   
	   boolean[] portsTrue = {
			   true,
			   true,
			   false,
			   false,
			   false
	   };
	   
	   String[] paths = {
			   "",
			   "/test",
			   "/no space",
			   "/anything?options=true",
			   "/",
			   "/this/is/a/file.txt",
			   "/not//allowed"
	   };
	   
	   boolean[] pathsTrue = {
			   true,
			   true,
			   false,
			   true,
			   true,
			   true,
			   false
	   };
	   
	   
	   for(int a = 0; a < schemes.length; a++) {
		   for(int b = 0; b < addresses.length; b++) {
			   for(int c = 0; c < ports.length; c++) {
				   for(int d = 0; d < paths.length; d++) {
					   
					   StringBuilder builder = new StringBuilder();
					   boolean truth = true;
					   
					   builder.append(schemes[a]);
					   truth &= schemesTrue[a];
					   
					   builder.append(addresses[b]);
					   truth &= addressesTrue[b];
					   
					   builder.append(ports[c]);
					   truth &= portsTrue[c];
					   
					   builder.append(paths[d]);
					   truth &= pathsTrue[d];
					   
					   String url = builder.toString();
					   
					   try {
						   assertTrue(urlVal.isValid(url) == truth);
					   } catch (junit.framework.AssertionFailedError e) { // for junit assertion failures (isValid returned the wrong boolean)
						   System.out.println("FAIL: \"" + url + "\" was found to be " + (!truth ? "" : "in") + "valid by isValid but it was expected to be " + (truth ? "" : "in") + "valid");
					   } catch ( Exception e) { // for any java exception (some exception was thrown by the isValid function)
						   System.out.println("FAIL: \"" + url + "\" threw the exception " + e.toString());
				   	   }
				   }
			   }
		   }
	   }
	   
   }
   


}
