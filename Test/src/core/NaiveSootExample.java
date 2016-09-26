package core;

public class NaiveSootExample {
	
	public static void main(String[] args) {
		
		String jdkLibPath = "/usr/lib/jvm/java-7-openjdk-amd64/jre/lib/";
		
		String classpath = "bin"
				+ ":" + jdkLibPath + "rt.jar"
				+ ":" + jdkLibPath + "jsse.jar";
		
		soot.Main.main(new String[] {
				"-soot-class-path", classpath,
				"tests.Main",
				"-f", "J"				
		});
	}

}
