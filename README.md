@author 
	kartik vishwakarma
	12-11-2018

	Implementation of LRU and MRU, page replacement policy in database.

	Given a large dataset, with limited buffer size less than dataset, page replacement policy
	is required to avoid total page fault.

	Practically, after certain number of buffer, MRU perform better than LRU, after hot point
	Both, MRU and LRU have same number of page fault.

	Generally Hot point:
						size of inner relational table + 1;



(Generating relational datasets):
---------------------------------
compile:
	g++ page_ref_pattern.cpp -o page_ref_pathern -std=c++11
run:
	./page)ref_pattern


(Running LRU & MRU policy):
----------------------------
compile:
	g++ page_replacement_policy.cpp -o page_replacement_policy -std=c++11
run:
	./page_replacement_policy