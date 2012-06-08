/* from Lounge<C++>

template<class ret, class ...param_types)
class function_interface {
public:
   virtual ret operator()(param_types... ps)=0;
   virtual ~function_interface ()=0;
};
 
template<class functor, class ret, class ...param_types>
class function_impl : function_interface<ret, param_types...> {
    functor data;
    public:
    function_impl(functor d) :data(std::move(d)) {}
    virtual ret operator()(param_types... ps) {return data();}
};
 
template<class ret, class ...param_types>
class function {
    std::unique_ptr<function_interface<ret, param_types...>> ptr;
public:
    template<class functor>
    function(functor d) :ptr(new function_impl<functor, ret, param_types...>(std::move(d)) {}
    ret operator()(param_types... ps) {return (*ptr)();}
};

*/