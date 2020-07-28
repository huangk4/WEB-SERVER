objects = mian.o ThreadPool.o MyNetwork.o Http_Server.o
WEB_SERVER: $(objects)
	g++ -std=c++11 -pthread -o WEB_SERVER $(objects)

main.o: main.cpp pch.h Task.h ThreadPool.h MyNetwork.h
	g++ -c -std=c++11 -pthread main.cpp
	
Http_Server.o: Http_Server.cpp Http_Server.h pch.h CheckOS.h
	g++ -c -std=c++11 Http_Server.cpp

MyNetwork.o: MyNetwork.cpp CheckOS.h pch.h Task.h MyNetwork.h ThreadPool.h Http_Server.h
	g++ -c -std=c++11 MyNetwork.cpp

ThreadPool.o: ThreadPool.cpp pch.h Task.h ThreadPool.h
	g++ -c -std=c++11 -pthread ThreadPool.cpp

clean:
	rm $(objects)

