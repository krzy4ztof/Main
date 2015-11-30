package trash;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class okno extends Frame{
	/*Window for debugging*/
	
	private static ImageIcon img = new ImageIcon();

	public okno(ImageIcon p_img) {
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				dispose();
				System.exit(0);
			}	
		});
		img=p_img;
//		System.out.println(img);
		setVisible(true);
		setBounds(0,0,200, 200);
		setTitle("Okno");
//		MapSettingsPanel MSP = new MapSettingsPanel(new ApplicationManager());
//		MSP.activate(3,4);
//		System.out.println("okno koniec");
	}
	
	@Override
	public void paint(Graphics g){
	
		g.setPaintMode();
		g.drawImage(img.getImage(),0,0,
		getSize().width/2, getSize().height/2,
		getBackground(), this);
	//	Color.RED,this);
	}
	
	public static void main (String[] args){
		//ImageIcon l_img = new ImageIcon("");
		//okno p_okno = new okno (l_img);

		StringBuffer strbuf = new StringBuffer("");
		int i;
		System.out.println("napisz:");
	/*	try{
			while(true){
			i = System.in.read();
			strbuf.append(new String().charAt(i));
			}
		} catch (Exception e){};
		System.out.println(new String().charAt(10));
		System.out.println(strbuf);
		System.out.println(strbuf.toString());
		strbuf = new StringBuffer(":");
		strbuf.append(":");
		System.out.println(strbuf.toString());*/
		
		
/*		String s2 =new String("bfiwfbwifnwi");
		DataInputStream in3;
		
    try {
      in3 = new DataInputStream(
          new ByteArrayInputStream(s2.getBytes()));
      while(true)
      System.out.print((char)in3.readByte());
    } catch(Exception e) {
    	System.out.println();	
      System.err.println("End of stream");
    }
	*/



	char c;
	StringBuffer strng = new StringBuffer();

/*	try {
		while ((c=(char)System.in.read()) != '\n')
			strng.append(c);
	} catch (Exception e) {};
	System.out.println(strng.toString());*/
	
	try {
		while ((c=(char)System.in.read()) != '\n')
		{
			System.out.println(strng.toString());	
			strng.append(c);
		}
	} catch (Exception e) {};		
	System.out.println(strng.toString()+" "+1);
	System.out.println("jfdiwf"+" "+100);
	

	}
}

