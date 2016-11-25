#include "songlist.h"

SongList::SongList()
{
	head = nullptr;
	size = 0;
}


SongList::SongList(int reserve)
{
	head = nullptr;
	size = 0;
}


SongList::~SongList()
{
	Node * curr = head;

	while (head != NULL)
	{
		curr = head->next;
		delete head;

		head = curr;
	}
}

void SongList::print() const
{
	Node *	curr;
	std::cout << "DataBass Songs" << std::endl;
	int idx = 1;
	for(curr=head; curr; curr=curr->next)
	{

		curr->data.print();
		std::cout << "Index:   " << idx << std::endl << std::endl;
		idx++;
	}
}

void SongList::loadSongs(const char fileName[])
{
	ifstream in;
	Song tempSong;
	char otitle[128];
	char oartist[128];
	char ominutes[128];
	char oseconds[128];
	char oalbum[128];

	in.open(fileName);
	if (!in)
	{
		in.clear();
		cerr << endl << "Fail to open " << fileName << " for input!" << endl << endl;
		exit(1);
	}

	in.get(otitle, 128, ';');
	while (!in.eof())
	{
		in.get();							//remove field seperator ';'	
		in.get(oartist, 128, ';');
		in.get();
		in.get(ominutes, 128, ';');
		in.get();
		in.get(oseconds, 128, ';');
		in.get();
		in.get(oalbum, 128, '\n');
		in.ignore(100, '\n');				//remove record seperator '\n'

		tempSong.set(TITLE, otitle);
		tempSong.set(ARTIST, oartist);
		tempSong.set(MINUTES, ominutes);
		tempSong.set(SECONDS, oseconds);
		tempSong.set(ALBUM, oalbum);

		addEntry(tempSong);
		in.get(otitle, 128, ';');

	}
	in.close();

}

void SongList::searchp(const char name[], int idx) const
{
	char	current[128];

	std::cout << "Search " << name << std::endl;
	Node* curr;

	for (curr = head; curr; curr = curr->next)
	{
		curr->data.get(idx, current);

		if (strcmp(name, current) == 0)
		{
			curr->data.print();
			std::cout << "Index: " << idx + 1 << std::endl << std::endl;
		}
	}
}



void SongList::saveSong(const char fileName[])
{
	Node * curr;
	ofstream		out;
	char otitle[128];
	char oartist[128];
	char ominutes[128];
	char oseconds[128];
	char oalbum[128];

	out.open(fileName);
	if (!out)
	{
		out.clear();
		cerr << endl << "Fail to open " << fileName << " for output!" << endl << endl;
		exit(1);
	}

	for (curr = head; curr; curr = curr->next)
	{
		curr->data.get(TITLE, otitle);
		curr->data.get(ARTIST, oartist);
		curr->data.get(MINUTES, ominutes);
		curr->data.get(SECONDS, oseconds);
		curr->data.get(ALBUM, oalbum);

		out << otitle << ';' << oartist << ';' << ominutes << ';' << oseconds << ';' << oalbum << endl;
	}

	out.close();

}

void SongList::remove(int idx)
{
	int index = 0;
	char name[128];
	Node* curr;

	if (idx == 0)
	{
		head = head->next;
		return;
	}

	for (curr = head; curr; curr = curr->next)
	{
		if (index == idx - 1)
		{
			delete curr->next;
			curr->next = curr->next->next;
		}
		index++;
	}
}

int SongList::getSize() const
{
	return size;
}

void SongList::addEntry(Song& song)
{

	Song tempSong;
	char title[128];
	char otitle[128];

	song.get(TITLE, title);

	Node * newNode = new Node(song);

	Node * prev = NULL;
	Node * curr = head;

	while (curr)
	{
		curr->data.get(TITLE, otitle);
		if (strcmp(title, otitle) < 0)
			break;

		prev = curr;
		curr = curr->next;
	}

	newNode->next = curr;

	if (!prev)
		head = newNode;
	else
		prev->next = newNode;

	size++;
}
