#pragma once
#include <string>
#include "file_hash_data.h"

namespace flaber {

	class file_reader
	{

	public:

		Singleton(Singleton &other) = delete;

    	void operator=(const Singleton &) = delete;


    	static file_reader *get_instance();


	protected:
	    file_reader()
	    {
	    }

    static file_reader* instance;

	private:
		

		std::shared_ptr<char> buffer;
		
	};
	
	/*
	class Singleton
	{
	  private:
	    static std::unique_ptr<Singleton> instance;
	    // Конструкторы и оператор присваивания недоступны клиентам
	    Singleton(параметры конструктора) {...}
	    Singleton( const Singleton& );  
	    Singleton& operator=( Singleton& );
	public:
	    static Singleton* init(параметры конструктора) {
	        assert(instance == nullptr);
	        instance = std::make_unique<Singleton>(параметры конструктора);
	        return instance.get();
	    } 
	    static Singleton* getInstance() {
	        assert(instance != nullptr);
	        return instance.get();
	    }
	}
	*/
}