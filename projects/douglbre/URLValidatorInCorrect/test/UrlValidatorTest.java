

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   //You can use this function to implement your manual testing	   
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String[] trueList = {
			   "http://www.google.com",
			   "http://www.google.com/",
			   "FTP://www.google.com",
			   "h3t://www.google.com",
			   "http://anything.org",
			   "http://anything.net",
			   "https://www.google.com",
	   };
	   
	   String[] falseList = {
			   "http://www.google.com//",
			   "3ht://www.google.com",
			   "aaa://blahblah.net",
	   };
	   
	   for(int i = 0; i < trueList.length; i++) {
		   boolean result = urlVal.isValid(trueList[i]);
		   System.out.println(result + ": " + trueList[i]);
	   }
	   
	   for(int i = 0; i < falseList.length; i++) {
		   boolean result = urlVal.isValid(falseList[i]);
		   System.out.println(!result + ": " + falseList[i]);
	   }
	   
	   for(int i = 0; i < trueList.length; i++) {
		   assertTrue(urlVal.isValid(trueList[i]));
	   }
	   
	   for(int i = 0; i < falseList.length; i++) {
		   assertFalse(urlVal.isValid(falseList[i]));
	   }
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
