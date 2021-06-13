/*
Read more about this at 
https://stackoverflow.com/questions/48199813/how-to-use-condition-to-check-if-typename-t-is-integer-type-of-float-type-in-c#comment83380712_48199813
*/

template<> 
struct get_data_type<true>       //Do the calculations in 64 bit integer when edge weight is integer type 
{
	using type = int64_t;
};

template<> 
struct get_data_type<false>  //Do the calculations in long double when edge weights are in floating point
{
 	using type = long double;
};
