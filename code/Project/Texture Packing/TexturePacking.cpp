#include "TexturePacking.h"

int paintflag = 0;
TexturePacking::TexturePacking(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.calculateButton, SIGNAL(clicked()), this, SLOT(ClickButtom()));
}

void TexturePacking::ClickButtom()
{
	paintflag = 1; //calculation flag
	update();	  //call paintEvent()
}

void TexturePacking::paintEvent(QPaintEvent *event)
{
	int zoom = 2;
	int lrec_x = 50, rrec_x = 700;
	int lrec_y = 200, rrec_y = 200;
	int maxheight = 750;
	QPainter background(this);
	QPixmap pix;
	pix.load("strawberry.ico");
	background.drawPixmap(530, 200, 100, 100, pix);

	if (paintflag == 1) //implement calculation
	{
		int strip_width;
		int min_height;
		int area;
		int i;
		vector<Rectangle>::iterator iter;
		QString str;
		str = ui.WidthEdit->text();
		int width = str.toInt() * zoom;
		str = ui.OptimalHeightEdit->text();
		int optimal_height = str.toInt() * zoom;
		str = ui.NumEdit->text();
		int recnum = str.toInt();
		str = ui.IterEdit->text();
		int k = str.toInt();
		RandomRectangles(width, optimal_height, recnum); //generate random cases
		vector<Rectangle> rec_set = GetRectangle(strip_width);
		vector<Rectangle> optimal_rec_set = GetOptimalSolution(strip_width);
		clock_t start, finish;
		double totaltime;

		if (LengthCheck(rec_set, strip_width) == false)
		{
			return;
		}

		if (ui.Algorithm_1->isChecked()) //call algorithm 1
		{
			start = clock(); //calculate running time
			min_height = IterativeFindSolution(rec_set, strip_width, k);
			finish = clock(); //calculate running time
		}
		else if (ui.Algorithm_2->isChecked()) //call algorithm 2
		{
			start = clock(); //calculate running time
			for (i = 0; i < k; i++)
				min_height = FFDH(rec_set, strip_width);
			finish = clock(); //calculate running time
		}
		else if (ui.Algorithm_3->isChecked()) //call algorithm 3
		{
			start = clock(); //calculate running time
			for (i = 0; i < k; i++)
				min_height = SAS(rec_set, strip_width);
			finish = clock(); //calculate running time
		}
		else //do nothing
		{
			return;
		}

		area = SumArea(rec_set);
		totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
		str = QString::fromStdString(to_string(min_height / 2));
		ui.HeightEdit->setText(str);
		str = QString::fromStdString(to_string(1.0 * min_height / optimal_height));
		ui.RatioEdit->setText(str);
		string stringinit = to_string(totaltime);
		stringinit = stringinit.substr(0, stringinit.size() - 3) + "s";
		str = QString::fromStdString(stringinit);
		ui.TimeEdit->setText(str);
		str = QString::fromStdString(to_string(area * 1.0 / (strip_width * min_height)));
		ui.UltilizationEdit->setText(str);

		QPainter p;
		p.begin(this);
		//define a pen for drawing
		QPen pen;
		pen.setWidth(2);
		pen.setColor(QColor(0, 0, 0)); //set color
		pen.setStyle(Qt::SolidLine);
		//create a brush
		QBrush brush;
		brush.setColor(Qt::white);		   //set color for filling
		brush.setStyle(Qt::Dense4Pattern); //set style
		p.setPen(pen);
		p.setBrush(brush);
		p.drawRect(lrec_x, lrec_y, strip_width, maxheight); 
		p.drawRect(rrec_x, rrec_y, strip_width, maxheight);
		//draw all rectangles in rec_set
		brush.setColor(Qt::black); //reset color
		p.setBrush(brush);
		for (iter = rec_set.begin(); iter != rec_set.end(); iter++)
		{
			p.drawRect(lrec_x + (*iter).get_x(), lrec_y + (*iter).get_y(), (*iter).get_width(), (*iter).get_height());
		}
		for (iter = optimal_rec_set.begin(); iter != optimal_rec_set.end(); iter++)
		{
			p.drawRect(rrec_x + (*iter).get_x(), rrec_y + (*iter).get_y(), (*iter).get_width(), (*iter).get_height());
		}

		p.end();
	}
	paintflag = 0;
}