/* sample_plugin.cc

   g++ -c -std=c++0x -I /home/jeremy/local/include/ -I build/x86_64/include/mldb/ -I build/x86_64/include/ sdk/sample/sample_plugin.cc

   docker run -i quay.io/datacratic/mldb_sdk:jeremy_latest /bin/sh -c '/usr/bin/g++ -c -std=c++0x -I /opt/include/mldb -I /opt/include -x c++ -o out.o - && cat out.o' < sdk/sample/sample_plugin.cc > sample_plugin.o

   docker run -i -v `pwd`:/source:ro quay.io/datacratic/mldb_sdk:jeremy_latest bash -c '/usr/bin/g++ -c -std=c++0x -I /opt/include -x c++ -o out.o /source/sdk/sample/sample_plugin.cc'
 */

#include "mldb/soa/types/value_description.h"
#include "mldb/server/function.h"

using namespace Datacratic::MLDB;
using namespace std;

struct HelloWorldFunction: public Datacratic::MLDB::Function {

    HelloWorldFunction(Datacratic::MLDB::MldbServer * server,
                       Datacratic::PolyConfig config,
                       std::function<bool (Json::Value)> onProgress)
        : Datacratic::MLDB::Function(server)
    {
    }

    virtual Datacratic::Any getStatus() const
    {
        return std::string("A-OK");
    }

    virtual FunctionInfo getFunctionInfo() const
    {
        FunctionInfo result;
        result.output.addPin("hello", std::make_shared<Datacratic::MLDB::StringValueInfo>());
        return result;
    }

    virtual FunctionOutput apply(const FunctionApplier & applier,
                                 const FunctionContext & context) const
    {
        FunctionOutput result;
        ExpressionValue world("world", Datacratic::Date::now());
        result.set("hello", world);
        return result;
    }
};

static RegisterFunctionType<HelloWorldFunction, int>
regSqlQueryFunction("hello.world",
                    "Sample function that always returns hello = \"world\"",
                    "No documentation available");


