WEB_SERVER: Task.o ThreadPool.o MyNetwork.o main.o
	g++ -std=c++11 -o WEB main.o Task.o MyNetwork.o ThreadPool.o

main.o: main.cpp pch.h Task.h ThreadPool.h MyNetwork.h
	g++ -c -std=c++11 main.cpp

Task.o: Task.cpp pch.h Task.h
	g++ -c -std=c++11 Task.cpp

MyNetwork.o: MyNetwork.cpp CheckOS.h pch.h Task.h MyNetwork.h ThreadPool.h
	g++ -c -std=c++11 MyNetwork.cpp

ThreadPool.o: ThreadPool.cpp pch.h Task.h ThreadPool.h
	g++ -c -std=c++11 ThreadPool.cpp

clean:
	rm main.o Task.o MyNetwork.o ThreadPool.o

