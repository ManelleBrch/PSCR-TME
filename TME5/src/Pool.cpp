#include "Pool.h"
namespace pr{
	Pool::Pool(int qsize) : queue(qsize) {}

	void Pool::stop(){
		queue.setBlocking(false);
		for(auto & t : threads){
			t.join();
		}
	}

	void poolWalker(Queue<Job> & queue){
		while(true){
			Job *j = queue.pop();
			if(j == nullptr){
				break;
			}
			j->run();
			delete j;
		}
	}

	void Pool::start(int nbthread){
		for(int i=0; i<nbthread; i++){
			threads.emplace_back(poolWalker, std::ref(queue));
		}
	}

	void Pool::submit(Job * job){
		queue.push(job);
	}

	Pool::~Pool(){}

}
