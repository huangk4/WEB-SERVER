objects = mian.o Task.o ThreadPool.o MyNetwork.o
WEB_SERVER: $(objects)
	g++ -std=c++11 -thread -o WEB $(objects)

main.o: main.cpp pch.h Task.h ThreadPool.h MyNetwork.h
	g++ -c -std=c++11 -thread main.cpp

Task.o: Task.cpp pch.h Task.h
	g++ -c -std=c++11 -thread Task.cpp

MyNetwork.o: MyNetwork.cpp CheckOS.h pch.h Task.h MyNetwork.h ThreadPool.h
	g++ -c -std=c++11 -thread MyNetwork.cpp

ThreadPool.o: ThreadPool.cpp pch.h Task.h ThreadPool.h
	g++ -c -std=c++11 -thread ThreadPool.cpp

clean:
	rm WEB $(objects)

