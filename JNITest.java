package newjni;

import java.util.HashMap;
import java.lang.Integer;

public class JNITest {


  static {
    System.loadLibrary("ProcessHash");
  }

  
  public static native HashMap<String, String> getMap();
  
  public static void main(String[] args) {
   
    HashMap<String, String> result = getMap();
    System.out.println("key    pID     processName    cpuUsage    memusage   diskusage      netusage     userOwns");
    
    
    int keyInt = 1;
    for (String keys : result.keySet()){
            String key = Integer.toString(keyInt); 
            
            String value = result.get(key); 
            
            //String value = ;  
            System.out.println(key + "     " + value);
            keyInt++;
} 
    
    
    
   
  }
}