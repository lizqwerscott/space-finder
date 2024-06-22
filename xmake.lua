-- 定义项目名和版本
set_project("space-finder")
set_version("0.0.1")

-- 设置编译选项
set_languages("c++20")
add_rules("mode.debug", "mode.release")
add_cxxflags("-g", "-Wall")

package("box2d")
    set_urls("https://github.com/erincatto/box2d.git")
    add_deps("cmake")
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
    end)
package_end()

package("slt")
    set_kind("library")
    add_deps("box2d")
    add_deps("sfml", {system = true})
    add_urls("https://github.com/lizqwerscott/Slt-GameEngine.git")

    on_install(function (package)
        local configs = {}
        if package:config("shared") then
            configs.kind = "shared"
        end
        import("package.tools.xmake").install(package, configs)
    end)
package_end()
add_requires("slt")
add_requires("nlohmann_json", {system = true})

local function get_all_cpp_files(dir)
    local files = {}
    for _, file in ipairs(os.files(path.join(dir, "**.cpp"))) do
        table.insert(files, file)
    end
    return files
end

-- 获取所有 .cpp 文件
local cpp_files = get_all_cpp_files("src")

target("main")
   set_kind("binary")
   set_basename("main")

   add_files(cpp_files)
   -- add_packages("nlohmann_json")
   add_packages("slt")

-- 自定义编译后处理
after_build(function (target)
    -- 获取构建目录
    local buildir = target:targetdir()
    -- 定义资源目录和目标目录
    local resource_dir = path.join(os.projectdir(), "resource")
    local target_dir = path.join(buildir, "resource")
    -- 复制资源文件夹到目标目录
    os.cp(resource_dir, target_dir)
end)

-- 自定义安装脚本
on_install(function (target)
    -- 获取安装目录
    local installdir = target:installdir()
    -- 定义资源目录和目标目录
    local resource_dir = path.join(os.projectdir(), "resource")
    local target_dir = path.join(installdir, "resource")
    -- 复制资源文件夹到目标目录
    os.cp(resource_dir, target_dir)
end)
