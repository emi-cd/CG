import java.io.File;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.IOException;

import java.awt.Color;

public class Img {

	public static void main(String args[]) {
		MyImage image;
		image = JpegFileReader.read("imgs/renga2.jpg");

		try{
			File file = new File("renga3.txt");
			PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(file)));
		
			for(int i = 0; i < image.height; i++) {
				for(int j = 0; j < image.width; j++) {
					Color color = image.getColor(j, i);
					pw.print(color.getRed());
					pw.print(' ');
					pw.print(color.getGreen());
					pw.print(' ');
					pw.print(color.getBlue());
					pw.print(' ');
				}
			}
			pw.close();
		}catch(IOException e){
			System.out.println(e);
		}

	}
}
