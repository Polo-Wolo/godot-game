# Import the environment from godot-cpp/SConstruct
env = SConscript("godot-cpp/SConstruct")

# Add your own include path
env.Append(CPPPATH=["src/"])

# Get all source files
sources = Glob("src/*.cpp")

# Build the shared library
library = env.SharedLibrary(
    "demo/bin/BouncingSprite{}{}".format(env["suffix"],env["SHLIBSUFFIX"]),
    source = sources
)
# library = env.SharedLibrary(
#     "demo/bin/BouncingSprite" + env["SHLIBSUFFIX"], 
#     source=sources
# )

# Make it the default target
Default(library)