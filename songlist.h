#ifndef SONGLIST_H
#define SONGLIST_H

#include <fstream>
using namespace std;
#include "song.h"

const int INIT_CAP = 128;

class SongList
{
public:
	SongList();
	SongList(int reserve);

	~SongList();

	bool get(int idx, Song& song) const;
	bool search(const char name[], int idx, Song& match) const;
	void searchp(const char name[], int idx) const;
	int getSize() const;
	void print() const;
	void remove(int idx);
	void loadSongs(const char fileName[]);
	void saveSong(const char fileName[]);
	void addEntry(Song& song);

private:
	struct Node
	{
		Song	data;
		Node *	next;

		Node(Song& aData)
		{
			char otitle[128];
			char oartist[128];
			char ominutes[128];
			char oseconds[128];
			char oalbum[128];

			aData.get(TITLE, otitle);
			aData.get(ARTIST, oartist);
			aData.get(MINUTES, ominutes);
			aData.get(SECONDS, oseconds);
			aData.get(ALBUM, oalbum);

			data.set(TITLE, otitle);
			data.set(ARTIST, oartist);
			data.set(MINUTES, ominutes);
			data.set(SECONDS, oseconds);
			data.set(ALBUM, oalbum);
			
			next = NULL;
		}
	};

	Node*	head;
	int		size;
};
#endif