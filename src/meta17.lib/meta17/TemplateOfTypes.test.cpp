#include <meta17/TemplateOfTypes.h>

using namespace meta17;

template<class... Ts>
struct MyWrap {};

using MyTemplate = TemplateOfTypes<MyWrap>;
