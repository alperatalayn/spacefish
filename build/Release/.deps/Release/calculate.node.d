cmd_Release/calculate.node := ln -f "Release/obj.target/calculate.node" "Release/calculate.node" 2>/dev/null || (rm -rf "Release/calculate.node" && cp -af "Release/obj.target/calculate.node" "Release/calculate.node")
