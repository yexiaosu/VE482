l6: list.c list.h logic.c logic.h txtPlugin.c csvPlugin.c cmd.c interface.c interface.h pluginDiscover.c pluginDiscover.h pluginManager.h pluginManager.c
	clang -c -fPIC -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla list.c list.h logic.c logic.h  pluginManager.h pluginManager.c txtPlugin.c
	clang -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla -shared -o libtxt.so list.o logic.o pluginManager.o txtPlugin.o
	clang -c -fPIC -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla list.c list.h logic.c logic.h  pluginManager.h pluginManager.c csvPlugin.c
	clang -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla -shared -o libcsv.so list.o logic.o pluginManager.o csvPlugin.o
	clang -g -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla -c cmd.c interface.c interface.h pluginDiscover.c pluginDiscover.h pluginManager.h pluginManager.c
	clang -g -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla cmd.o interface.o pluginDiscover.o -ldl pluginManager.o -o l6
	clang -g -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=integer cmd.o interface.o pluginDiscover.o -ldl pluginManager.o -o l6_memory_check

