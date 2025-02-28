// api.cpp: application programming interface demonstration of fixed-size, arbitrary precision multi-dimensional logarithmic number systems
//
// Copyright (C) 2022-2023 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/utility/directives.hpp>
#include <universal/number/lns2b/lns2b.hpp>
#include <universal/number/lns2b/table.hpp>
#include <universal/number/cfloat/cfloat.hpp>  // bit field comparisons
#include <universal/verification/test_suite.hpp>

// Regression testing guards: typically set by the cmake configuration, but MANUAL_TESTING is an override
#define MANUAL_TESTING 0
// REGRESSION_LEVEL_OVERRIDE is set by the cmake file to drive a specific regression intensity
// It is the responsibility of the regression test to organize the tests in a quartile progression.
//#undef REGRESSION_LEVEL_OVERRIDE
#ifndef REGRESSION_LEVEL_OVERRIDE
#undef REGRESSION_LEVEL_1
#undef REGRESSION_LEVEL_2
#undef REGRESSION_LEVEL_3
#undef REGRESSION_LEVEL_4
#define REGRESSION_LEVEL_1 1
#define REGRESSION_LEVEL_2 1
#define REGRESSION_LEVEL_3 1
#define REGRESSION_LEVEL_4 1
#endif

template<typename Real>
inline constexpr Real bases(const Real&, const Real& base) {
	std::cout << "         base : " << base << '\n';
	return base;
}

template<typename Real, typename BaseHead, typename ...OtherBases>
inline constexpr Real bases(const Real& x, const BaseHead& bHead, const OtherBases& ...otherBases) {
	std::cout << "bases<>  base : " << bHead << '\n';
	return bases(x, static_cast<Real>(otherBases)...);
}

template<typename Real, unsigned nrBases>
class lnsBases {
public:

private:
	Real base[nrBases];
};

int main()
try {
	using namespace sw::universal;

	std::string test_suite = "lns2b API demonstration";
	std::string test_tag = "api";
	bool reportTestCases = false;
	int nrOfFailedTestCases = 0;

	ReportTestSuiteHeader(test_suite, reportTestCases);

	// float x{ 1.0f };
	// bases(x, 2.5f, 3, 5, 7, 9);

	// generate a value table for lns2b<5,2>
	GenerateLns2bTable<5,2>(std::cout);

	{
		lns2b<8, 3> l(1);
		std::cout << to_binary(l) << " : " << l << " : " << color_print(l) << '\n';
		l.debugConstexprParameters();

		l.setbits(0xf5);
		std::cout << to_binary(l) << " : " << l << " : " << color_print(l) << '\n';
		std::cout << to_binary(l.extractExponent(0), 4) << " : " << to_binary(l.extractExponent(1), 4) << '\n';

		std::cout << dynamic_range(l) << '\n';
	}

	// important behavioral traits
	ReportTrivialityOfType<lns2b<8, 2>>();

	// default behavior
	{
		std::cout << "+---------    default lns2b bahavior   --------+\n";
		using Real = lns2b<8, 3>;
		Real a(1.0f), b(1.0f), c;
//		ArithmeticOperators<Real>(a, b);
		a = 1;  // integer assignment
		b = 1;
		c = a + b;
//		ReportBinaryOperation(a, "+", b, c);
	}

	{
		std::cout << "+---------    dynamic ranges of 8-bit lns2b<> configurations   --------+\n";
//		std::cout << symmetry_range(lns2b<8, 0>()) << '\n';
		std::cout << symmetry_range(lns2b<8, 1>()) << '\n';
		std::cout << symmetry_range(lns2b<8, 2>()) << '\n';
		std::cout << symmetry_range(lns2b<8, 3>()) << '\n';
		std::cout << symmetry_range(lns2b<8, 4>()) << '\n';
		std::cout << symmetry_range(lns2b<8, 5>()) << '\n';
		std::cout << symmetry_range(lns2b<8, 6>()) << '\n';
	}

	// configuration
	{
		std::cout << "+---------    arithmetic operators with explicit alignment bahavior   --------+\n";
//		using lns2b16 = lns2b<16, 5, std::uint16_t>;
//		ArithmeticOperators<lns2b16>(1.0f, 1.0f);

//		using lns2b24 = lns2b<24, 5, std::uint32_t>;
//		ArithmeticOperators<lns2b24>(1.0f, 1.0f);
	}

	{
		std::cout << "+---------    Dynamic ranges of lns2b<> configurations   --------+\n";
		std::cout << dynamic_range(lns2b< 4, 2>()) << '\n';
		std::cout << dynamic_range(lns2b< 8, 3>()) << '\n';
		std::cout << dynamic_range(lns2b<12, 4>()) << '\n';
		std::cout << dynamic_range(lns2b<16, 5>()) << '\n';
		std::cout << dynamic_range(lns2b<20, 6>()) << '\n';
	}

	{
		std::cout << "+---------    constexpr and specific values   --------+\n";
		constexpr size_t nbits = 10;
		constexpr size_t rbits = 3;
		using Real = lns2b<nbits, rbits>;  // BlockType = uint8_t, behavior = Saturating

//		CONSTEXPRESSION Real a{}; // zero constexpr
//		std::cout << type_tag<Real>(a) << '\n';  // TODO: type_tag doesn't work for lns2b

		// TODO: needs a constexpr version of log2() function
//		CONSTEXPRESSION Real b(1.0f);  // constexpr of a native type conversion
//		std::cout << to_binary(b) << " : " << b << '\n';

		CONSTEXPRESSION Real c(SpecificValue::minpos);  // constexpr of a special value in the encoding
		std::cout << to_binary(c) << " : " << c << " == minpos" << '\n';

		CONSTEXPRESSION Real d(SpecificValue::maxpos);  // constexpr of a special value in the encoding
		std::cout << to_binary(d) << " : " << d << " == maxpos" << '\n';
	}

	{
		std::cout << "+---------    extreme values   --------+\n";
		constexpr size_t nbits = 10;
		constexpr size_t rbits = 3;
		using Real = lns2b<nbits, rbits>;  // BlockType = uint8_t, behavior = Saturating

		Real a, b, c;

		a = INFINITY;
		b = 2;
		c = a / b;
		std::cout << "scale(" << a << ") = " << a.scale() << '\n';
		std::cout << "scale(" << b << ") = " << b.scale() << '\n';
		ReportBinaryOperation(a, "/", b, c);
	}

	{
		std::cout << "+---------    exceptions   ---------+\n";
		using lns2b = sw::universal::lns2b<16, 8, uint16_t>;
		lns2b a = lns2b(0.0f);
		lns2b b = -lns2b(0.0);
		// if (a != b) std::cout << "you can't compare indeterminate NaN\n";
		if (a.isnan() && b.isnan()) std::cout << "PASS: both +lns2b(0) and -lns2b(0) are indeterminate\n";
		std::cout << "+lns2b(0.0f): " <<  lns2b(0.0f) << "\n";
		std::cout << "-lns2b(0.0f): " << -lns2b(0.0f) << "\n";
	}

	{
		std::cout << "+---------    comparison to classic floats   --------+\n";
		using lns2b = lns2b<16, 8, std::uint16_t>;
		using Real = cfloat<16, 5, std::uint16_t>;
		lns2b a;
		Real b;
		static_assert(std::is_trivially_constructible<lns2b>(), "lns2b<> is not trivially constructible");
		a = 1;
//		std::cout << std::setw(80) << type_tag(a) << " : " << to_binary(a, true) << " : " << color_print(a, true) << " : " << float(a) << '\n';
		b = 1;
		std::cout << std::setw(80) << type_tag(b) << " : " << to_binary(b, true) << " : " << color_print(b, true) << " : " << float(b) << '\n';
	}
	
	ReportTestSuiteResults(test_suite, nrOfFailedTestCases);
	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Uncaught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
