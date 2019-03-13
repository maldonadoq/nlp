#ifndef _CLASSIFY_H_
#define _CLASSIFY_H_

#include <boost/algorithm/string.hpp> 
#include <bits/stdc++.h> 
#include <fstream>
#include <vector>
#include <list>

std::vector<std::string> tokenize(std::string data){
	std::vector<std::string> data_tokens; 
	boost::split(data_tokens, data, boost::is_any_of(" ")); 
	return data_tokens;
}	

class cclassify{
private:
	std::vector<std::list<std::vector<std::string > > > m_class;
	std::vector<unsigned > m_ntkn;
	std::vector<std::string> m_vocabulary;
	unsigned m_total;
public:
	cclassify(unsigned _nclass){
		this->m_class = std::vector<std::list<std::vector<std::string > > >(_nclass);
		this->m_ntkn = std::vector<unsigned >(_nclass,0);
		this->m_total = 0;
	}

	void inside(std::string);
	void classify(std::string);
	unsigned all_rclass(unsigned, std::string);
	void find_class(std::string);

	~cclassify(){
		this->m_class.clear();
	}
};


void cclassify::inside(std::string data){
	unsigned i;

	for(i=0; i<m_vocabulary.size(); i++){
		if(m_vocabulary[i]==data)	return;
	}

	m_vocabulary.push_back(data);
}

void cclassify::classify(std::string _filename){
	std::ifstream file(_filename);
	if(!file.is_open()){
		std::cout << "error! cvs wrong!!\n";
		return;
	}

	std::string tmp;
	unsigned i;
	std::vector<std::string> vt;
	while(file.good()){
		getline(file,tmp,'|');
		i = stoi(tmp);					// classes index
		getline(file,tmp,'\n');
		this->m_total++;				// prior total

		vt = tokenize(tmp);				// tokens
		this->m_class[i].push_back(vt);	// clasees
		this->m_ntkn[i] += vt.size();	// number of tokens

		for(i=0; i<vt.size(); i++)	inside(vt[i]);
	}

	file.close();
}	

unsigned cclassify::all_rclass(unsigned i, std::string data){
	unsigned tmp = 0;

	for(auto it = this->m_class[i].begin(); it != this->m_class[i].end(); it++) {
		for(unsigned j=0; j<(*it).size(); j++)
			if(data == (*it)[j])	tmp+=1;
	}

	return tmp;
}

void cclassify::find_class(std::string data){
	unsigned size = m_class.size();
	unsigned i,j;

	std::vector<double> prior(size);
	std::vector<double> result(size);

	for(i=0; i<size; i++){
		prior[i] = (double)m_class[i].size()/(double)m_total;			
		//std::cout << prior[i] << "\n";
	}

	std::vector<std::string> data_tokens = tokenize(data); 

	double tmp;
	for(i=0; i<size; i++){
		result[i] = prior[i];

		for(j=0; j<data_tokens.size(); j++){
			tmp = all_rclass(i, data_tokens[j]);
			result[i] *= (tmp+1)/(m_ntkn[i]+m_vocabulary.size());
		}

		std::cout << std::setprecision(6) << "class " << i << ": " << result[i] << "%\n";
	}		
}

#endif