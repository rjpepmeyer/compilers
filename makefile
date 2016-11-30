flairs:
	g++ -std=c++0x src/flairs.cpp -o flairs

flairv:
	g++ -std=c++0x src/flairv.cpp -o flairv

# Alias of flairv

flairf:
	g++ -std=c++0x src/flairv.cpp -o flairf

flairp:
	g++ -std=c++0x src/flairp.cpp -o flairp

flairc:
	g++ -std=c++0x src/flairc.cpp -o flairc

clean:
	rm -f *~
	rm -f *.o
	rm -f flair?
