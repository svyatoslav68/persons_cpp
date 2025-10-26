#include <boost/lexical_cast.hpp>
//#include <boost/tuple/tuple.hpp>
#include <tuple>
#include <iostream>

template <typename T>
std::string s_quote(T input) {
	return boost::lexical_cast<std::string>(input);
}

template <>
std::string s_quote<std::string>(std::string input) {
	return '\"' + input + '\"';
}

template <int IDX, int MAX, typename... Args>
struct PRINT_TUPLE {
	static void print(std::ostream & strm, const std::tuple<Args...>& t){
	//static void print(std::ostream & strm, const boost::tuple<Args...>& t){
		strm << s_quote(std::get<IDX>(t)) << (IDX+1==MAX ?"":",");
		//strm << boost::get<IDX>(t) << (IDX+1==MAX ?"":",");
		PRINT_TUPLE<IDX+1,MAX,Args...>::print(strm,t);
	}
};

template <int MAX, typename... Args>
struct PRINT_TUPLE<MAX,MAX,Args...> {
	static void print(std::ostream& strm, const std::tuple<Args...>& t){
	//static void print(std::ostream& strm, const boost::tuple<Args...>& t){
	}
};

template <typename... Args>
std::ostream& operator << (std::ostream& strm, const std::tuple<Args...>& t)
//std::ostream& operator << (std::ostream& strm, const boost::tuple<Args...>& t)
{
	strm << "[";
	PRINT_TUPLE<0,sizeof...(Args),Args...>::print(strm,t);
	return strm << "]";
}

