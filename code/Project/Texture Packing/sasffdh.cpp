#include "TexturePacking.h"

int FFDH(vector<Rectangle>& rec, int strip_width)  //the core of  the FFDH algorithm
{
	sort(rec.begin(), rec.end(), sortFFDH);        //sort the rectangles based on their height
	rec[0].set_bl_x(0);
	rec[0].set_bl_y(0);
	int w = rec[0].get_width();
	int h = rec[0].get_height();
	vector<Layer> lay; 
	lay.clear();
	Layer curlay(w, h, 0);                        //init the first layer
	lay.push_back(curlay);

	for (int i = 1; i < rec.size(); i++)          //when the rectangle set is not none
	{
		int j;
		for (j = 0; j < lay.size(); j++)
		{
			int emptyw = strip_width - lay[j].get_width();         //can used to place the rectangle
			if (rec[i].get_width() <= emptyw)
			{
				rec[i].set_bl_x(lay[j].get_width());                             //set the rectangle's position
				rec[i].set_bl_y(lay[j].get_floorh());
				lay[j].set_width(lay[j].get_width() + rec[i].get_width());       //update this layer's width
				break;
			}
		}
		if (j == lay.size())            //if all the existed layer can't place the rectangle,then create a layer
		{
			curlay.set_width(rec[i].get_width());
			curlay.set_height(lay[j - 1].get_height() + rec[i].get_height());
			curlay.set_floorh(lay[j - 1].get_height());
			lay.push_back(curlay);
			rec[i].set_bl_x(0);
			rec[i].set_bl_y(lay[j].get_floorh());
		}
	}
	return (lay.back()).get_height();   //return the height
}

bool sortFFDH(Rectangle& rec1, Rectangle& rec2)      //the sorting order of the FFDH algorithm
{
	return rec1.get_height() > rec2.get_height();
}

int SAS(vector<Rectangle> &rec, int strip_width)     //the core of the SAS algorithm
{
	enum { LNARROW, LWIDE }choice1, choice2;         //LNARROW means that last procedure,we put the narrow rectangles and we need to put the wide next
	int way = 0;
	int curX = 0;
	int curY = 0;
	int height = 0;
	Area curArea;    //curArea: the area can used to place the rectangle
	int choice;

	vector<Rectangle> narrowRec;       //narrowRec:the set of the narrow rectangles
	vector<Rectangle> wideRec;         //wideRec:the set of the wide rectangles
	vector<Rectangle>::iterator itRec;   //sort the rectangles 
	for (itRec = rec.begin(); itRec < rec.end(); itRec++)
	{
		if ((*itRec).get_width() >= (*itRec).get_height())
			wideRec.push_back(*itRec);
		else
			narrowRec.push_back(*itRec);
	}
	rec.clear();     //clear the rec for placing the rectangles in our placing order

	sort(narrowRec.begin(), narrowRec.end(), sortNarrow);
	sort(wideRec.begin(), wideRec.end(), sortWide);
	
	while (narrowRec.size() || wideRec.size())    //when the set of the rectangles is not none
	{
		if (narrowRec.size() && wideRec.size())   //when the wide and narrow both exist
		{
			if (narrowRec[0].get_height() > wideRec[0].get_height())   //if the highest narrow is higher than the highest wide rectangle,we first put the narrow
			{
				placeFirstRec(rec, narrowRec, curX, curY, height);
				choice = LNARROW;
			}
			else   
			{
				placeFirstRec(rec, wideRec, curX, curY, height);
				choice = LWIDE;
			}
		}
		else if (narrowRec.size())    //if there is no wide rectangles
		{
			placeFirstRec(rec, narrowRec, curX, curY, height);
			choice = LNARROW;
		}
		else                          //if there is no narrow rectangles
		{
			placeFirstRec(rec, wideRec, curX, curY, height);
			choice = LWIDE;
		}
		
		defineArea(curArea, curX, strip_width, curY, height);   //set the area to place the rectangles
		if (choice == LNARROW)  
			placeWideRec(rec, narrowRec, wideRec, curArea, way);
		else     
			placeNarrowRec(rec, narrowRec, wideRec, curArea, way);
	}
	return height;
}

void placeNarrowRec(vector<Rectangle> &rec,  vector<Rectangle> &narrowRec, vector<Rectangle> &wideRec,Area& curArea,int& way)
{
	enum { LNARROW, LWIDE }choice1, choice2;
	if (narrowRec.size())                            //if there exists the narrow rectangle
	{
		int i;
		for (i = 0; i < narrowRec.size(); i++)       //to find the narrow rectangles to fit the area
		{
			int x_length = curArea.get_xr() - curArea.get_xl();
			int y_length = curArea.get_ya() - curArea.get_yb();
			if (x_length >= narrowRec[i].get_width() && y_length >= narrowRec[i].get_height())
				break;
		}
		if (i == narrowRec.size())    
			return;

		int tw = narrowRec[i].get_width();
		int th= narrowRec[i].get_height();
		setRecPosition(rec, narrowRec, curArea, i);   //set the x & y value for the rectangle in the rec set
		Area aboveArea(curArea.get_xl(), curArea.get_xl() + tw, curArea.get_yb() + th, curArea.get_ya()); //define this rectangle's above area
		placeNarrowRec(rec, narrowRec,wideRec,aboveArea,way);    //to put the narrow rectangles in its above area
		Area rightArea(curArea.get_xl() + tw, curArea.get_xr(),curArea.get_yb(), curArea.get_ya()); //define this rectangle's right area
		placeNarrowRec(rec,narrowRec,wideRec,rightArea,way);     //to put the narrow rectangles in its right area
	}
	else if (way == LWIDE)   
	{
		way = LNARROW;
		return;
	}
	else         //if there is no narrow rectangle
		placeWideRec(rec,narrowRec,wideRec,curArea,way);
}

void placeWideRec(vector<Rectangle> &rec, vector<Rectangle> &narrowRec, vector<Rectangle> &wideRec,Area& curArea,int& way) // the procedure of placing wideRec rectangles
{
	enum { LNARROW, LWIDE }choice1, choice2;
	int x_length = curArea.get_xr() - curArea.get_xl();
	int y_length = curArea.get_ya() - curArea.get_yb();
	int txl = curArea.get_xl();

	if (wideRec.size() && x_length >= wideRec.back().get_width())  //to see if the narrowset wide rectangle can fit: if there exists a wide rectangle to fit
	{
		int i;
		for (i = 0; i < wideRec.size(); i++)
			if (curArea.get_xr() - curArea.get_xl() >= wideRec[i].get_width())   
				break;
		if (i == wideRec.size())
			return;
		int j;
		for (j = i; j < wideRec.size(); j++)       //select the widest rectangle to fit
		{
			if (curArea.get_ya() - curArea.get_yb() >= wideRec[j].get_height())         //find the first rectangle to place
				break;
		}
		if (j == wideRec.size())  
			return;

		int curX = wideRec[j].get_width() + curArea.get_xl();
		int curY = curArea.get_yb();
		while (j != wideRec.size() && curArea.get_ya() - curArea.get_yb() >= wideRec[j].get_height())  
		{
			if (curArea.get_ya() - curArea.get_yb() >= wideRec[i].get_height())   //if the rectangles'height is lower than this layer's highest wide rectangle
			{
				int tw = wideRec[j].get_width();
				int th = wideRec[j].get_height();
				int tx = wideRec[j].get_x();
				setRecPosition(rec, wideRec, curArea, j);    //set the x&y value of this rectangle in the rec set
				curArea.set_yb(curArea.get_yb() + th);
				if (curArea.get_xr() - (curArea.get_xl() + tw) > 0)   //if this layer still has length but can't put a wide rectangle continusly,we put narrow
				{
					way = LWIDE;
					if (narrowRec.size())       
					{
						Area narrowArea(curArea.get_xl() + tw, curArea.get_xr(), curArea.get_yb()-th, curArea.get_ya());
						placeNarrowRec(rec, narrowRec, wideRec, narrowArea, way);
						curArea.set_xr(curArea.get_xl() + tw);
					}
				}
			}
			else
				break;
			Area wideArea(curX, curArea.get_xr(), curY, curArea.get_ya());   //put the wide rectangles in a new layer
			placeWideRec(rec, narrowRec, wideRec, wideArea, way); 
		}
			
	}
	else     //there doesn't have a wide rectangle to replace
	{
		way = LWIDE;
		placeNarrowRec(rec, narrowRec, wideRec,curArea,way);
	}
}

void defineArea(Area& curArea, int xl, int xr, int yb, int ya)   //set the boundary value of the area
{
	curArea.set_xl(xl);
	curArea.set_xr(xr);
	curArea.set_yb(yb);
	curArea.set_ya(ya);
}

void placeFirstRec(vector<Rectangle>& rec, vector<Rectangle>& curRec, int& curX, int& curY, int& height) //to place the first rectangle of a new layer
{
	curRec[0].set_bl_x(0);
	curRec[0].set_bl_y(height);
	rec.push_back(curRec[0]);
	curY = height;
	curX = curRec[0].get_width();
	height = height + curRec[0].get_height();
	curRec.erase(curRec.begin());
}

void setRecPosition(vector<Rectangle>& rec, vector<Rectangle>& curRec, Area& curArea, int index)  //to put the rectangle in the rec set and set its x&y values
{
	curRec[index].set_bl_x(curArea.get_xl());
	curRec[index].set_bl_y(curArea.get_yb());
	rec.push_back(curRec[index]);
	curRec.erase(curRec.begin() + index);
}

bool sortNarrow(Rectangle& rec1, Rectangle& rec2)     //to define the sort order of the narrow rectangles
{
	if (rec1.get_height() != rec2.get_height())
		return rec1.get_height() > rec2.get_height();
	else
		return rec1.get_width() > rec2.get_width();
}

bool sortWide(Rectangle& rec1, Rectangle& rec2)      //to define the sort order of the wide rectangles
{
	if (rec1.get_width() != rec2.get_width())
		return rec1.get_width() > rec2.get_width();
	else
		return rec1.get_height() > rec2.get_height();
}


