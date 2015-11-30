package trash;

import java.util.LinkedList;

import javax.swing.ImageIcon;

public class ImagesList extends LinkedList {
    /*
    class description:

    structure format:
    ImageList[x] - 2-element list,
    all informations about "x" Theme
    ImageList[x][0] - String, Theme name
    ImageList[x][1] - list, variable ThemeImages,
    informations about images for "x" Theme
    ImageList[x][1][y] - 2-element list,
    variable NameAndFileImage,
    informations about "y" jpeg in "x" Theme
    ImageList[x][1][y][0] - String, nazwa obrazka ("zewn�trzna")
    ImageList[x][1][y][1] - String, jpeg filename
    ImageList[x][1][y][2] - ImageIcon, jpeg pixels
    ImageList[x][1][y][3] - int, image identifier. Cannot be equal 0.
     */
//	private String getThemeName(int x){
//		/* zwraca nazw� x-tego Tematu*/
//		return (String)((LinkedList)this.get(x)).get(0);
//	//	return (String)(((LinkedList)this.get(x)).get(0));	tez dobrze dzia�a
//	}
//	public String getIconName(int x, int y){
//		/* zwraca nazw� zewn�trzn� y-tego obrazka w x-tym Temacie*/
//		return (String)((LinkedList)((LinkedList)((LinkedList)this.get(x)).get(1)).get(y)).get(0);
//	}
//    private String getIconFileName(int x, int y) {
//        /* zwraca nazw� pliku y-tego obrazka w x-tym Temacie*/
//        if ((x < 0) || (x >= this.size())) {
//            // nie ma tematu o tym numerze
//            return "";
//        } else if ((y < 0) || (y >= this.getThemeSize(x))) {
//            // nie ma ikony o tym numerze w temacie
//            return "";
//        } else {
//            return (String) ((LinkedList) ((LinkedList) ((LinkedList) this.get(x)).get(1)).get(y)).get(1);
//        }
//	}
//
//	public ImageIcon getIconPixels(int x, int y){
//		/* zwraca y-ty obrazek w x-tym Temacie*/
//		return (ImageIcon)((LinkedList)((LinkedList)((LinkedList)this.get(x)).get(1)).get(y)).get(2);
//	}
//	private Integer getIconId(int x, int y){
//		/* zwraca id y-tego obrazka w x-tym Temacie*/
//		return (Integer)((LinkedList)((LinkedList)((LinkedList)this.get(x)).get(1)).get(y)).get(3);
//	}
//	private String getIconIdString(int x, int y){
//		/* returns id of y Image in x Theme. Id is given as String */
//		Integer Id = this.getIconId(x,y);
//		return this.TransferIdtoString(Id);
//
//	}
//	private int getThemeSize(int x){
//		/*zwraca ilo�� obrazk�w w x-tym Temacie
//		(Aby sprawdzi� ilosc Temat�w wystarczy this.size())
//		*/
//		return ((LinkedList)((LinkedList)this.get(x)).get(1)).size();
//	}
//	private int getThemeNumber(String name){
//		/*zwraca numer Tematu na podstawie jego nazwy
//		Obs�uga b��du - lub zero w przypadku b��du
//		*/
//		int res=0;
//		for (int i=0;i<this.size();i++)
//		{
//			if (this.getThemeName(i).equals(name)==true)
//				res=i;
//		}
//		return res;
//	}	
//	public String translateFilenameToId(String filename){
//		/*
//		 * Returns Id that identifies Filename
//		 */
//		int themes = this.size();
//		int icons;
//		int i,j;
//		for (i=0; i<themes;i++){
//			icons = this.getThemeSize(i);
//			for (j=0;j<icons;j++){
//				if (filename.equals(this.getIconFileName(i,j))){
//					return this.getIconIdString(i,j);
//				}
//			}
//		}
//		return "000";
//	}
//	public boolean getIconPosition(String filename,int[] pos){
//		/* Na podstawie nazwy pliku filename zwraca
//		numer tematu w kt�rym znajduje si� ikona (pos[0]) i
//		numer ikony (pos[1]).Zwraca false gdy nie ma
//		takiej ikony*/
//		int themes = this.size();
//		int icons;
//		int i,j;
//		for (i=0; i<themes;i++){
//			icons = this.getThemeSize(i);
//			for (j=0;j<icons;j++){
//				if (filename.equals(this.getIconFileName(i,j))){
//					pos[0] = i; pos[1] =j;
//					return true;
//				}
//			}
//		}
//		return false;
//	}	
//	private String TransferIdtoString(Integer IntId)
//	{
//		if ((IntId >= 0 ) && (IntId <10))
//		{
//			return "00"+IntId.toString();
//
//		}else if ((IntId >= 10 ) && (IntId <100))
//		{
//			return "0"+IntId.toString();
//		}else if ((IntId >= 100 ) && (IntId <1000))
//		{
//			return IntId.toString();
//		}else{
//			return "000";
//		}
//	}
}
