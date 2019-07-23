#include "plugin.h"
#include "SlowBoost.h"
#include <cedar/processing/ElementDeclaration.h>

void pluginDeclaration(cedar::aux::PluginDeclarationListPtr plugin)
{
    cedar::proc::ElementDeclarationPtr summation_decl
    (
        new cedar::proc::ElementDeclarationTemplate <SlowBoost>("Utilities")
    );
    plugin->add(summation_decl);
}
