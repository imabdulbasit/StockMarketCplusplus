# include "includes.h"
# include "Attributes.h"
# include "StockTickers.h"
# include <random>
# include <chrono>
using namespace std;

int  del(BST* tree, node* t1, node* t2, node* t3, node* t4, node* t5, char* ticker) {
	BST* n = new BST;
	avlTree* t = new avlTree;
	struct node* n1 = (struct node*)
		new struct node;
	n->root = tree->search__(ticker);
	if (n->root == NULL)
		return -1;
	//--------for volume--------
	n1 = t->search_key(t1, n->root->volume);
	if (n1->l.countlist() == 1) {
		t->deleteNode(t1, n1->key);
	}
	else {
		for (int i = 0; i < n1->l.countlist(); i++) {
			if (n1->l.atindex(i) == ticker) {
				n1->l.del(i);
			}
		}
	}

	//---------for open---------
	n1 = t->search_key(t2, n->root->open);
	if (n1->l.countlist() == 1) {
		t->deleteNode(t2, n1->key);
	}
	else {
		for (int i = 0; i < n1->l.countlist(); i++) {
			if (n1->l.atindex(i) == ticker) {
				n1->l.del(i);
			}
		}
	}

	//-----------for close------------
	n1 = t->search_key(t3, n->root->close);
	if (n1->l.countlist() == 1) {
		t->deleteNode(t3, n1->key);
	}
	else {
		for (int i = 0; i < n1->l.countlist(); i++) {
			if (n1->l.atindex(i) == ticker) {
				n1->l.del(i);
			}
		}
	}

	//------------for high-------------
	n1 = t->search_key(t4, n->root->high);
	if (n1->l.countlist() == 1) {
		t->deleteNode(t4, n1->key);
	}
	else {
		for (int i = 0; i < n1->l.countlist(); i++) {
			if (n1->l.atindex(i) == ticker) {
				n1->l.del(i);
			}
		}
	}

	//------------for low-----------

	n1 = t->search_key(t5, n->root->low);
	if (n1->l.countlist() == 1) {
		t->deleteNode(t5, n1->key);
	}
	else {
		for (int i = 0; i < n1->l.countlist(); i++) {
			if (n1->l.atindex(i) == ticker) {
				n1->l.del(i);
			}
		}
	}

	// --------for ticker-----------

	tree->remove(ticker);
	return 0;

}

void inRangeMenu() {

	cout << "\n\t1. Volume within a specified range" << endl;
	cout << "\t2. Opening within a specified range" << endl;
	cout << "\t3. Closing within a specified range" << endl;
	cout << "\t4. Daily High within a specified range" << endl;
	cout << "\t5. Daily Low within a specified range" << endl;

	cout << "\nEnter your choice : ";
}

int main(int argc, char** argv) {
	string t = "IBXD";
	char f[20];
	char* x;
	char ch;
	int lower, upper, in_range_choice;
	std::random_device rd;
	BST *tick = new BST;
	/* Random number generator */
	std::default_random_engine generator(rd());
	/* Distribution on which to apply the generator */
	std::uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFFFFFFF);
	char r[20];
	char* aux;
	avlTree* t1 = new avlTree;
	struct node* volAVL = NULL;

	avlTree* t2 = new avlTree;
	struct node* openAVL = NULL;

	avlTree* t3 = new avlTree;
	struct node* closeAVL = NULL;

	avlTree* t4 = new avlTree;
	struct node* highAVL = NULL;

	avlTree* t5 = new avlTree;
	struct node* lowAVL = NULL;
	std::ifstream file("stock.txt");
	std::string str;
	auto startTime = chrono::high_resolution_clock::now();

	while (std::getline(file, str)) {
		cout << str << "  ";
		strcpy_s(r, str.c_str());
		aux = _strdup(r);
		int volume = (distribution(generator) % 100000000);
		int high = (rand() % 1000000), low = (rand() % 1000000), close = (rand() % 1000000), open = (rand() % 1000000);
		tick->insert(aux, volume, high, low, open, close);
		volAVL = t1->insert(volAVL, aux, volume);
		openAVL = t2->insert(openAVL, aux, open);
		closeAVL = t3->insert(closeAVL, aux, close);
		highAVL = t4->insert(highAVL, aux, high);
		lowAVL = t5->insert(lowAVL, aux, low);
	}
	auto finishTime = chrono::high_resolution_clock::now();
	cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::minutes>(finishTime - startTime).count()) << " minutes" << endl;
	cout << "\n\n" << endl;
	
	string sticker;
	int volume, open, close, high, low;
	do {

		{

			cout << "\n\n";
			cout << "a - Display all stocks" << endl;
			cout << "b - Delete a stock" << endl;
			cout << "c - Insert stock" << endl;
			cout << "d - Display top 100 stocks by Volume" << endl;
			cout << "e - Display Bottom 100 stocks by Volume" << endl;
			cout << "f - Save stocks data to a file" << endl;
			cout << "g - Search a stock " << endl;
			cout << "h - Update Stock" << endl;
			cout << "i - Total number of stocks" << endl;
			cout << "j - Display stocks by Range" << endl;
			cout << "k - Display top 100 stocks by Opening Price" << endl;
			cout << "l - Display bottom 100 stocks by Opening Price" << endl;
			cout << "m - Display top 100 stocks by Closing Price" << endl;
			cout << "n - Display bottom 100 stocks by Closing Price" << endl;
			cout << "o - Display top 100 stocks by Daily High" << endl;
			cout << "p - Display bottom 100 stocks by Daily High" << endl;
			cout << "q - Display top 100 stocks by Daily Low" << endl;
			cout << "r - Display bottom 100 stocks by Daily Low" << endl;
			cout << "s - Exit program" << endl;
			cout << "\nEnter your choice (a-r): ";
			cin >> ch;
			switch (ch)
			{
			case 'a':
				startTime = chrono::high_resolution_clock::now();
				tick->display();
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::minutes>(finishTime - startTime).count()) << " minutes" << endl;
				break;

			case 'b':
				cout << "Enter the stock ticker : ";

				cin >> sticker;

				strcpy_s(f, sticker.c_str());
				x = _strdup(f);
				startTime = chrono::high_resolution_clock::now();
				if (del(tick, volAVL, openAVL, closeAVL, highAVL, lowAVL, x) == -1)
					cout << "Stock not found!" << endl;
				else
				{
					cout << "Stock successfully deleted!" << endl;
				}
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count()) << " microseconds" << endl;

				break;

			case 'c':
				cout << "Enter Stock Data:\n";
				cout << "Enter ticker : ";
				cin >> sticker;
				cout << "\nEnter volume : ";
				cin >> volume;
				cout << "\nEnter close : ";
				cin >> close;
				cout << "\nEnter open : ";
				cin >> open;
				cout << "\nEnter high : ";
				cin >> high;
				cout << "\nEnter low : ";
				cin >> low;
				strcpy_s(f, sticker.c_str());
				x = _strdup(f);
				startTime = chrono::high_resolution_clock::now();
				tick->insert(x, volume, high, low, open, close);
				volAVL = t1->insert(volAVL, x, volume);
				openAVL = t2->insert(openAVL, x, open);
				closeAVL = t3->insert(closeAVL, x, close);
				highAVL = t4->insert(highAVL, x, high);
				lowAVL = t5->insert(lowAVL, x, low);
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count()) << " microseconds" << endl;
				break;

			case 'd':
				startTime = chrono::high_resolution_clock::now();
				t1->nlargest(100, volAVL, "Volume");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'e':
				startTime = chrono::high_resolution_clock::now();
				t1->nsmallest(100, volAVL, "Volume");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'f':
				startTime = chrono::high_resolution_clock::now();
				tick->saveFile();
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nData successfully saved!" << endl;
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) / 1000.0 << " seconds" << endl;
				break;

			case 'g':
				cout << "Enter the stock ticker : ";

				cin >> sticker;
				strcpy_s(f, sticker.c_str());
				x = _strdup(f);
				startTime = chrono::high_resolution_clock::now();
				tick->displaynode(x);
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count()) << " microseconds" << endl;
				break;

			case 'h':
				cout << "Enter Stock Data:\n";
				cout << "Enter the stock ticker : ";
				cin >> sticker;
				strcpy_s(f, sticker.c_str());
				x = _strdup(f);
				cout << "\nEnter volume : ";
				cin >> volume;
				cout << "\nEnter close : ";
				cin >> close;
				cout << "\nEnter open : ";
				cin >> open;
				cout << "\nEnter high : ";
				cin >> high;
				cout << "\nEnter low : ";
				cin >> low;
				startTime = chrono::high_resolution_clock::now();

				if (del(tick, volAVL, openAVL, closeAVL, highAVL, lowAVL, x) == -1)
				{
					cout << "No stock found! ";

				}
				else {
					tick->insert(x, volume, high, low, open, close);
					volAVL = t1->insert(volAVL, x, volume);
					openAVL = t2->insert(openAVL, x, open);
					closeAVL = t3->insert(closeAVL, x, close);
					highAVL = t4->insert(highAVL, x, high);
					lowAVL = t5->insert(lowAVL, x, low);
				}
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count()) << " microseconds" << endl;
				break;

			case 'i':
				startTime = chrono::high_resolution_clock::now();
				tick->count();
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'j':
				inRangeMenu();
				cin >> in_range_choice;

				switch (in_range_choice)
				{
				case 1:
					cout << "\n\tEnter lower bound : ";
					cin >> lower;
					cout << "\n\tEnter upper bound : ";
					cin >> upper;
					startTime = chrono::high_resolution_clock::now();
					t1->Inrange(volAVL, lower, upper);
					finishTime = chrono::high_resolution_clock::now();
					cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
					break;

				case 2:
					cout << "\n\tEnter lower bound : ";
					cin >> lower;
					cout << "\n\tEnter upper bound : ";
					cin >> upper;
					startTime = chrono::high_resolution_clock::now();
					t2->Inrange(openAVL, lower, upper);
					finishTime = chrono::high_resolution_clock::now();
					cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
					break;

				case 3:
					cout << "\n\tEnter lower bound : ";
					cin >> lower;
					cout << "\n\tEnter upper bound : ";
					cin >> upper;
					startTime = chrono::high_resolution_clock::now();
					t3->Inrange(closeAVL, lower, upper);
					finishTime = chrono::high_resolution_clock::now();
					cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
					break;

				case 4:
					cout << "\n\tEnter lower bound : ";
					cin >> lower;
					cout << "\n\tEnter upper bound : ";
					cin >> upper;
					startTime = chrono::high_resolution_clock::now();
					t4->Inrange(highAVL, lower, upper);
					finishTime = chrono::high_resolution_clock::now();
					cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
					break;

				case 5:
					cout << "\n\tEnter lower bound : ";
					cin >> lower;
					cout << "\n\tEnter upper bound : ";
					cin >> upper;
					startTime = chrono::high_resolution_clock::now();
					t5->Inrange(lowAVL, lower, upper);
					finishTime = chrono::high_resolution_clock::now();
					cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
					break;


				default:
					cout << "\n\tInvalid choice!" << endl;
					break;
				}

				break;

			case 'k':
				startTime = chrono::high_resolution_clock::now();
				t2->nlargest(100, openAVL, "Opening Price");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'l':
				startTime = chrono::high_resolution_clock::now();
				t2->nsmallest(100, openAVL, "Opening Price");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'm':
				startTime = chrono::high_resolution_clock::now();
				t3->nlargest(100, closeAVL, "Closing Price");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'n':
				startTime = chrono::high_resolution_clock::now();
				t3->nsmallest(100, closeAVL, "Closing Price");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'o':
				startTime = chrono::high_resolution_clock::now();
				t4->nlargest(100, highAVL, "Daily High");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'p':
				startTime = chrono::high_resolution_clock::now();
				t4->nsmallest(100, highAVL, "Daily High");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'q':
				startTime = chrono::high_resolution_clock::now();
				t5->nlargest(100, lowAVL, "Daily Low");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;

			case 'r':
				startTime = chrono::high_resolution_clock::now();
				t5->nsmallest(100, lowAVL, "Daily Low");
				finishTime = chrono::high_resolution_clock::now();
				cout << "\nExecution time : " << (chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count()) << " milliseconds" << endl;
				break;


			case 's':
				cout << "\nExiting program..." << endl;
				break;
			}			

		}
	}

	while (ch != 's');

	return 0;
}