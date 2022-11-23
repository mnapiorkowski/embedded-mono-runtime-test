#include <iostream>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/debug-helpers.h>

int main(int argc, char* argv[]) {
	/*
	 * Load the default Mono configuration file
	 */
	mono_config_parse(nullptr);

	/*
	 * Create a domain
	 */
	MonoDomain* domain = mono_jit_init("TestDomain");
	if (!domain) {
		std::cout << "mono_jit_init failed" << std::endl;
		return 1;
	}

	/*
	 * Open the executable
	 */
	const char* filename = "managed.exe";
	MonoAssembly* assembly = mono_domain_assembly_open(domain, filename);
	if (!assembly) {
		std::cout << "mono_domain_assembly_open failed" << std::endl;
		return 1;
	}

	// >>> MAIN METHOD <<<
	/*
	 * Run the Main method
	 */
	std::cout << "Running: Main()" << std::endl;
	mono_jit_exec(domain, assembly, argc, argv);

	// >>> STATIC METHOD <<<
	/*
	 * Get the image from the assembly
	 */
	MonoImage* image = mono_assembly_get_image(assembly);
	if (!image) {
		std::cout << "mono_assembly_get_image failed" << std::endl;
		return 1;
	}

	/*
	 * Build a method description object
	 */
	const char* static_method_desc_str = "Test:Hello()";
	MonoMethodDesc* static_method_desc = mono_method_desc_new(static_method_desc_str, false);
	if (!static_method_desc) {
		std::cout << "mono_method_desc_new failed" << std::endl;
		return 1;
	}

	/*
	 * Search for the method in the image
	 */
	MonoMethod* static_method = mono_method_desc_search_in_image(static_method_desc, image);
	if (!static_method) {
		std::cout << "mono_method_desc_search_in_image failed" << std::endl;
		return 1;
	}

	/*
	 * Run the static method
	 */
	std::cout << "Running the static method: " << static_method_desc_str << std::endl;
	mono_runtime_invoke(static_method, nullptr, nullptr, nullptr);

	// >>> NON-STATIC METHOD <<<
	/*
	 * Get the class
	 */
	MonoClass* test_class = mono_class_from_name(image, "", "Test");
	if (!test_class) {
		std::cout << "mono_class_from_name failed" << std::endl;
		return 1;
	}

	/*
	 * Create an instance of the class
	 */
	MonoObject* object = mono_object_new(domain, test_class);
	if (!object) {
		std::cout << "mono_object_new failed" << std::endl;
		return 1;
	}

	/*
	 * Call its default constructor
	 */
	mono_runtime_object_init(object);

	/*
	 * Build a method description object
	 */
	const char* method_desc_str = "Test:Add(int,int)";
	MonoMethodDesc* method_desc = mono_method_desc_new(method_desc_str, false);
	if (!method_desc) {
		std::cout << "mono_method_desc_new failed" << std::endl;
		return 1;
	}

	/*
	 * Search for the method in the image
	 */
	MonoMethod* method = mono_method_desc_search_in_image(method_desc, image);
	if (!method) {
		std::cout << "mono_method_desc_search_in_image failed" << std::endl;
		return 1;
	}

	/*
	 * Set the arguments for the method
	 */
	int a = 2137;
	int b = 420;
	void* args[] = {&a, &b};

	/*
	 * Run the method
	 */
	std::cout << "Running the method: " << method_desc_str << std::endl;
	MonoObject* result = mono_runtime_invoke(method, object, args, nullptr);

	/*
	 * Unbox and dereference the result
	 */
	int int_result = *(int*)mono_object_unbox(result);
	std::cout << a << " + " << b << " = " << int_result << std::endl;

	/*
	 * Clean up the domain
	 */
	mono_jit_cleanup(domain);
	return 0;
}
