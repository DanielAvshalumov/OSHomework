import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Scanner;

public class oshw1 {
    public static void main(String[] args) throws Exception {

        // Asks user for input and output file names
        // write() can be used to write to the screen, prompting the user, using the fd of 1 for the monitor 
        Scanner in = new Scanner(System.in);
        String inFile, outFile;
        System.out.println("Enter an the input file name");
        inFile = in.next();
        System.out.println("Enter your output file name");
        outFile = in.next();

        // Creates files 
        // open() is used for opening the input file
        // memfd_creat() is used for creating files, in this case will be our output file
        File inputText = new File(inFile+".txt");
        File outputText = new File(outFile+".txt");

        // Reader and writer created
        // read() is used that reads bytes from a file descriptor (fd) 0 that is the keyboard;
        BufferedReader br = new BufferedReader(new FileReader(inputText));
        FileWriter fw = new FileWriter(outputText);
        
        int ascii;
        int count = 0;
        int lines = 0;

        // Checks for non ASCII values and counts the lines with and without an asci value
        while((ascii = br.read()) != -1) {
            if(ascii < 256) {
                if(ascii == 10) {
                    lines++;
                }
                fw.append((char)ascii);
            } else {
                count++;
            }
        }

        System.out.println(count + " non ascii values have been found and " +( lines - count )+ " lines have beeen found without non ascii numbers");

        // kill() can be used to close the file writers and readers
        in.close();
        br.close();
        fw.close();

        // exit() is used to close the program
    }
}