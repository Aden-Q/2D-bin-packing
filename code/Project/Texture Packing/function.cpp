#include "TexturePacking.h"

vector<Rectangle> GetRectangle(int &strip_width) //read all required data from input
{
	vector<Rectangle> rec_set; //set of rectangles
	int rec_num;               //strip_width and rec_num are specified by user
	int width, height;         //rectangle parameters
	int i;
	ifstream infile;
	infile.open("random.txt");
	infile >> strip_width >> rec_num;
	for (i = 0; i < rec_num; i++)
	{
		infile >> height >> width;
		Rectangle rec(width, height);
		rec_set.push_back(rec);
	}
	return rec_set;
}

vector<Rectangle> GetOptimalSolution(int &strip_width) //read all required data from input
{
	vector<Rectangle> rec_set; //set of rectangles
	int rec_num;               //strip_width and rec_num are specified by user
	int width, height;         //rectangle parameters
	int x, y;
	int i;
	ifstream infile_shape;
	ifstream infile_position;
	infile_shape.open("random.txt");
	infile_position.open("optimal.txt");
	infile_shape >> strip_width >> rec_num;
	infile_position >> x >> y; //discard
	for (i = 0; i < rec_num; i++)
	{
		infile_shape >> height >> width;
		infile_position >> x >> y;
		Rectangle rec(width, height, x, y);
		rec_set.push_back(rec);
	}
	return rec_set;
}

bool LengthCheck(vector<Rectangle> &rec_set, int width)
{
	vector<Rectangle>::iterator iter;
	for (iter = rec_set.begin(); iter != rec_set.end(); iter++)
	{
		if ((*iter).get_height() < width + EPS || (*iter).get_width() < width + EPS)
			return true;
	}
	return false;
}

void PrintRectangles(vector<Rectangle> rec_set) //print all rectangle attributes in rectangle set
{
	vector<Rectangle>::iterator rec_iter;
	int w, h;
	for (rec_iter = rec_set.begin(); rec_iter != rec_set.end(); rec_iter++)
	{
		w = (*rec_iter).get_width();
		h = (*rec_iter).get_height();
		cout << "width: " << w << " height: " << h << " x: " << (*rec_iter).get_x() << " y: " << (*rec_iter).get_y() << endl;
	}
}

void PrintContour(vector<Segment> Contour) //print all segment attributes in contour
{
	vector<Segment>::iterator seg_iter;
	int xl, xr, y;
	for (seg_iter = Contour.begin(); seg_iter != Contour.end(); seg_iter++)
	{
		xl = (*seg_iter).get_xl();
		xr = (*seg_iter).get_xr();
		y = (*seg_iter).get_y();
		cout << "xl: " << xl << " xr: " << xr << " y: " << y << endl;
	}
}

void PrintSegment(Segment seg) //print attributes of a single segment
{
	int xl, xr, y;
	xl = seg.get_xl();
	xr = seg.get_xr();
	y = seg.get_y();
	cout << "xl: " << xl << " xr: " << xr << " y: " << y << endl;
}

bool SegmentLRSort(Segment a, Segment b) //function parameter in sort function
{
	return (a.get_xl() < b.get_xl());
}

vector<Segment>::iterator FindSegment(vector<Segment> &Contour, int flag) //find segment with minimum y or maximum y
{
	int y_low = 10000;
	int y_high = -1;
	int y;
	vector<Segment>::iterator seg_iter, rseg;

	if (flag == LOWEST)
	{
		for (seg_iter = Contour.begin(); seg_iter != Contour.end(); seg_iter++)
		{
			y = (*seg_iter).get_y();
			if (y < y_low)
			{
				rseg = seg_iter;
				y_low = y;
			}
		}
	}
	else if (flag == HIGHEST)
	{
		for (seg_iter = Contour.begin(); seg_iter != Contour.end(); seg_iter++)
		{
			y = (*seg_iter).get_y();
			if (y > y_high)
			{
				rseg = seg_iter;
				y_high = y;
			}
		}
	}
	return rseg;
}

vector<Rectangle>::iterator FindRectangle(vector<Rectangle> &rec_set, Rectangle &rec) //find if a rectangle is in rectangle set
{
	vector<Rectangle>::iterator rec_iter;
	for (rec_iter = rec_set.begin(); rec_iter != rec_set.end(); rec_iter++)
	{
		if ((*rec_iter).get_placed() == false && *rec_iter == rec)
			break;
	}
	return rec_iter;
}

void ConstructRCL(vector<Rectangle> &rec_set, vector<Rectangle> &RCL, int length, int delta_y) //construct a candidate list
{
	vector<Rectangle>::iterator rec_iter;
	int width, height;
	for (rec_iter = rec_set.begin(); rec_iter != rec_set.end(); rec_iter++)
	{
		width = (*rec_iter).get_width();
		height = (*rec_iter).get_height();
		if (width <= length && width + CANDIDATE_WIDTH >= length && height < delta_y + CANDIDATE_HEIGHT) //three constrains should be satisfied
			RCL.push_back(*rec_iter);
		else if (height <= length && height + CANDIDATE_WIDTH >= length && width < delta_y + CANDIDATE_HEIGHT) //rotate situation
		{
			(*rec_iter).rotate();
			RCL.push_back(*rec_iter);
		}
	}
}

void CombineSegment(vector<Segment> &Contour)
{
	vector<Segment>::iterator iter, next_iter;
	int flag = 0; //iteration flag
	int length;
	while (flag != 1)
	{
		for (iter = Contour.begin(); iter != Contour.end(); iter++)
		{
			if (flag == 1)
				break;
			next_iter = iter + 1;
			if (next_iter == Contour.end())
				flag = 1;
			else
			{
				if ((*iter).get_y() == (*next_iter).get_y())
				{
					length = (*next_iter).get_xr() - (*next_iter).get_xl();
					(*iter).set_xr((*iter).get_xr() + length);
					Contour.erase(next_iter);
					break;
				}
			}
		}
		if (iter == Contour.end())
			flag = 1;
	}
}

void LevelUpdate(vector<Segment> &Contour)
{
	vector<Segment>::iterator iter, left_iter, right_iter;
	iter = FindSegment(Contour, LOWEST);
	if (iter != Contour.end())
		right_iter = iter + 1;
	if (iter != Contour.begin())
		left_iter = iter - 1;
	if (iter == Contour.begin()) //the first segment is the lowest
	{
		if (right_iter != Contour.end())
		{
			(*iter).set_y((*right_iter).get_y());
			(*iter).set_xr((*right_iter).get_xr());
			Contour.erase(right_iter);
		}
	}
	else if (iter == Contour.end() - 1) //the last segment is the lowest
	{
		(*iter).set_y((*left_iter).get_y());
		(*iter).set_xl((*left_iter).get_xl());
		Contour.erase(left_iter);
	}
	else //middle case
	{
		int left_y = (*left_iter).get_y();
		int right_y = (*right_iter).get_y();
		if (left_y < right_y) //left segment is lower than right segment
		{
			(*iter).set_y((*left_iter).get_y());
			(*iter).set_xl((*left_iter).get_xl());
			Contour.erase(left_iter);
		}
		else if (left_y > right_y) //left segment is higher than right segment
		{
			(*iter).set_y((*right_iter).get_y());
			(*iter).set_xr((*right_iter).get_xr());
			Contour.erase(right_iter);
		}
		else //left segment and right segment have the same height
		{
			(*iter).set_y((*right_iter).get_y());
			(*iter).set_xl((*left_iter).get_xl());
			(*iter).set_xr((*right_iter).get_xr());
			Contour.erase(right_iter);
			Contour.erase(left_iter);
		}
	}
}

bool BestFit(vector<Rectangle> &unplaced, vector<Segment> &Contour, Rectangle &best_fit_rectangle) //return true for finded
{
	vector<Rectangle>::iterator rec_iter;
	vector<Segment>::iterator seg_iter_min_y, seg_iter_max_y;
	int length;
	int delta_y;
	int width, height;
	double min_evaluation = 10000; //minimum evaluation value should be satisfied, initialize large
	double cur_evaluation;

	seg_iter_min_y = FindSegment(Contour, LOWEST);  //find segment with minimum y in contour(iterator returned)
	seg_iter_max_y = FindSegment(Contour, HIGHEST); //find segment with maximum y in contour(iterator returned)
	length = (*seg_iter_min_y).get_xr() - (*seg_iter_min_y).get_xl();
	delta_y = (*seg_iter_max_y).get_y() - (*seg_iter_min_y).get_y();
	bool finded = false; //finded or not, 0 represents not finded, 1 for finded
	for (rec_iter = unplaced.begin(); rec_iter != unplaced.end(); rec_iter++)
	{
		width = (*rec_iter).get_width();
		height = (*rec_iter).get_height();
		if (width > length && height > length)
			continue;
		else if ((width > length) || (height > width && height < length))
		{
			(*rec_iter).rotate();
		}
		cur_evaluation = 1.0 * (length - (*rec_iter).get_width()) / (*rec_iter).get_height(); //evaluation function
		if (cur_evaluation < min_evaluation)
		{
			min_evaluation = cur_evaluation;
			best_fit_rectangle = *rec_iter;
			finded = true;
		}
	}
	return finded;
}

void FillRectangle(vector<Rectangle> &rec_set, vector<Segment> &Contour)
{
	int length;  //length of the lowest segment
	int delta_y; //height difference between the highest segment and the lowest segment
	int i;
	vector<Rectangle> RCL;               //restricted candidate list for rectangles
	vector<Rectangle> solution;          //partial solution list of rectangels
	vector<Rectangle> unplaced(rec_set); //partial solution list of rectangels, initialized all unplaced
	vector<Rectangle>::iterator rec_iter;
	vector<Segment>::iterator seg_iter_min_y, seg_iter_max_y;
	srand((unsigned)time(NULL)); //used to generate random number(for random choose)
	Rectangle best_fit_rectangle;

	//PrintRectangles(RCL);
	while (!unplaced.empty())
	{
		RCL.clear();                                    //clear restricted candidate list for each iteration
		seg_iter_min_y = FindSegment(Contour, LOWEST);  //find segment with minimum y in contour(iterator returned)
		seg_iter_max_y = FindSegment(Contour, HIGHEST); //find segment with minimum y in contour(iterator returned)
		length = (*seg_iter_min_y).get_xr() - (*seg_iter_min_y).get_xl();
		delta_y = (*seg_iter_min_y).get_y() - (*seg_iter_min_y).get_y();

		ConstructRCL(unplaced, RCL, length, delta_y); //use the lowest segment to construct restric candidate list RCL
		if (!RCL.empty())
		{
			i = rand() % RCL.size(); //random choose from RCL
			best_fit_rectangle = RCL[i];
		}
		else
		{
			if (BestFit(unplaced, Contour, best_fit_rectangle) == false) //RCL is empty so choose from unplcaed rectangles which best fit the segment
			{
				LevelUpdate(Contour);
				continue;
			}
		}
		rec_iter = FindRectangle(unplaced, best_fit_rectangle);
		solution.push_back(*rec_iter); //push into solution list
		unplaced.erase(rec_iter);      //remove the rectangle
		rec_iter = FindRectangle(rec_set, best_fit_rectangle);
		(*rec_iter).set_bl_x((*seg_iter_min_y).get_xl()); //place the rectangle
		(*rec_iter).set_bl_y((*seg_iter_min_y).get_y());  //place the rectangle
		(*rec_iter).place();
		if (length - best_fit_rectangle.get_width() == 0) //equivalent
		{
			(*seg_iter_min_y).set_y((*seg_iter_min_y).get_y() + best_fit_rectangle.get_height()); //update the segment on which rectangle is placed
			CombineSegment(Contour);                                                              //combine neighbour segments which have the same height
		}
		else
		{
			Segment seg((*seg_iter_min_y).get_xl(), (*seg_iter_min_y).get_xl() + best_fit_rectangle.get_width(), (*seg_iter_min_y).get_y() + best_fit_rectangle.get_height());
			(*seg_iter_min_y).set_xl((*seg_iter_min_y).get_xl() + best_fit_rectangle.get_width());
			Contour.push_back(seg);
			sort(Contour.begin(), Contour.end(), SegmentLRSort); //keep the left to right order of segments
			CombineSegment(Contour);                             //combine neightbour segments which have the same height
		}
	}
}

int IterativeFindSolution(vector<Rectangle> &rec_set, int strip_width, int k)
{
	vector<Rectangle>::iterator rec_iter;
	vector<Segment> Contour;      //segment set represent the contour
	vector<Segment> best_Contour; //segment set represent the contour
	vector<Segment>::iterator seg_iter;
	vector<Rectangle> best_rec_set;
	int i;
	int min_height = 10000;
	for (i = 0; i < k; i++) //simply iterate k times to seak for the best solution
	{
		Contour.clear();
		Segment seg(0, strip_width, 0);                                         //the bottom segment
		Contour.push_back(seg);                                                 //Contour initialization
		for (rec_iter = rec_set.begin(); rec_iter != rec_set.end(); rec_iter++) //reset all rectangles
			(*rec_iter).reset();
		FillRectangle(rec_set, Contour);			//seak for a simple solution
		VariableNeighbourSearch(rec_set, Contour, strip_width);		//improvment
		seg_iter = FindSegment(Contour, HIGHEST); //find the highest segment which represents the height of strip
		if ((*seg_iter).get_y() < min_height)     //update or not
		{
			min_height = (*seg_iter).get_y(); //record information for the best solution
			best_Contour = Contour;
			best_rec_set = rec_set;
		}
	}
	return min_height;
}

void VariableNeighbourSearch(vector<Rectangle> &rec_set, vector<Segment> &Contour, int width)
{
	vector<Rectangle>::iterator rec_iter;
	vector<Segment>::iterator seg_iter, seg_iter_prior, seg_low;
	int delta_y;
	int length;
	int i, k;
	k = rec_set.size()/5;
	for (i = 0; i < k; i++)
	{
		seg_iter = FindSegment(Contour, HIGHEST);	//find highest segment in contour
		int highest = (*seg_iter).get_y();			//store the highest segment
		(*seg_iter).set_y(0);
		seg_iter_prior = FindSegment(Contour, HIGHEST);		//last but one highest segment
		(*seg_iter).set_y(highest);					//recover the highest segment
		delta_y = (*seg_iter).get_y() - (*seg_iter_prior).get_y();
		for (rec_iter = rec_set.begin(); rec_iter != rec_set.end(); rec_iter++)
		{
			if ((*rec_iter).get_y() + (*rec_iter).get_height() == highest && (*rec_iter).get_width() == (*seg_iter).get_xr() - (*seg_iter).get_xl() && (*rec_iter).get_x() == (*seg_iter).get_xl())	//rec_iter points to the rectangle which is highest
				break;
		}
		if (rec_iter == rec_set.end())
			continue;
		if ((*rec_iter).get_width() < delta_y && (*rec_iter).get_height() <= width)
		{
			(*rec_iter).rotate();				//rotate this thin and tall rectangle, update segments
			(*seg_iter).set_y(highest - (*rec_iter).get_width());		//segment descent
			CombineSegment(Contour);			//combine segments with the same height
			while (1)				//find the lowest segment or implement level update
			{
				seg_low = FindSegment(Contour, LOWEST);
				length = (*seg_low).get_xr() - (*seg_low).get_xl();
				if (length >= (*rec_iter).get_width())	//place rectangle on it
				{
					(*rec_iter).set_bl_x((*seg_low).get_xl()); //place the rectangle
					(*rec_iter).set_bl_y((*seg_low).get_y());  //place the rectangle
					if (length - (*rec_iter).get_width() == 0) //equivalent
					{
						(*seg_low).set_y((*seg_low).get_y() + (*rec_iter).get_height()); //update the segment on which rectangle is placed
						CombineSegment(Contour);                                                              //combine neighbour segments which have the same height
					}
					else
					{
						Segment seg((*seg_low).get_xl(), (*seg_low).get_xl() + (*rec_iter).get_width(), (*seg_low).get_y() + (*rec_iter).get_height());
						(*seg_low).set_xl((*seg_low).get_xl() + (*rec_iter).get_width());
						Contour.push_back(seg);
						sort(Contour.begin(), Contour.end(), SegmentLRSort); //keep the left to right order of segments
						CombineSegment(Contour);                             //combine neightbour segments which have the same height
					}
					break;
				}
				else
					LevelUpdate(Contour);
			}
		}
	}
}

int SumArea(vector<Rectangle> &rec_set) //calculate the total rectangle area
{
	vector<Rectangle>::iterator iter;
	int sum_area = 0;
	for (iter = rec_set.begin(); iter != rec_set.end(); iter++)
		sum_area += (*iter).get_height()*(*iter).get_width();
	return sum_area;
}