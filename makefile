flairs:
	g++ -std=c++0x src/flairs.cpp -o flairs

flairv:
	g++ -std=c++0x src/flairv.cpp -o flairv

# Alias of flairv

flairf:
	g++ -std=c++0x src/flairf.cpp -o flairf

flairp:
	g++ -std=c++0x src/flairf.cpp -o flairp

clean:
	rm -f *~
	rm -f *.o
	rm -f flair?
