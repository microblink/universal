// division.cpp: functional tests for block binary number division
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <iomanip>
#include <typeinfo>

// minimum set of include files to reflect source code dependencies
#include <universal/blockbin/blockbinary.hpp>
// test helpers, such as, ReportTestResults
#include "../utils/test_helpers.hpp"
#include "../utils/blockbinary_helpers.hpp"

// enumerate all multiplication cases for an blockbinary<nbits,BlockType> configuration
template<size_t nbits, typename BlockType = uint8_t>
int VerifyDivision(std::string tag, bool bReportIndividualTestCases) {
	constexpr size_t NR_VALUES = (size_t(1) << nbits);
	using namespace std;
	using namespace sw::unum;

	cout << endl;
	cout << "blockbinary<" << nbits << ',' << typeid(BlockType).name() << '>' << endl;

	bool bReportOverflowCondition = false;
	int nrOfFailedTests = 0;
	int nrOfOverflows = 0;   // ref > maxpos
	int nrOfUnderflows = 0;  // ref < maxneg
	blockbinary<nbits, BlockType> a, b, result, refResult;
	int64_t aref, bref, cref;
	for (size_t i = 0; i < NR_VALUES; i++) {
		a.set_raw_bits(i);
		aref = int64_t(a.to_long_long()); // cast to long long is reasonable constraint for exhaustive test
		for (size_t j = 0; j < NR_VALUES; j++) {
			b.set_raw_bits(j);
			bref = int64_t(b.to_long_long()); // cast to long long is reasonable constraint for exhaustive test
			result = a / b;
		
			if (bref == 0) continue;
			cref = aref / bref;

			if (cref < -(1 << (nbits - 1))) {
				if (bReportOverflowCondition) cout << setw(5) << aref << " / " << setw(5) << bref << " = " << setw(5) << cref << " : ";
				if (bReportOverflowCondition) cout << "underflow: " << setw(5) << cref << " < " << setw(5) << -(1 << (nbits - 1)) << "(maxneg) assigned value = " << setw(5) << result.to_long_long() << " " << setw(5) << to_hex(result) << " vs " << to_binary(cref, 12) << endl;
				++nrOfUnderflows;
			}
			else if (cref > ((1 << (nbits - 1)) - 1)) {
				if (bReportOverflowCondition) cout << setw(5) << aref << " / " << setw(5) << bref << " = " << setw(5) << cref << " : ";
				if (bReportOverflowCondition) cout << "overflow: " << setw(5) << cref << " > " << setw(5) << (1 << (nbits - 1)) - 1 << "(maxpos) assigned value = " << setw(5) << result.to_long_long() << " " << setw(5) << to_hex(result) << " vs " << to_binary(cref, 12) << endl;
				++nrOfOverflows;
			}

			refResult.set_raw_bits(cref);
			if (result != refResult) {
				nrOfFailedTests++;
				if (bReportIndividualTestCases)	ReportBinaryArithmeticError("FAIL", "/", a, b, result, cref);
			}
			else {
				// if (bReportIndividualTestCases) ReportBinaryArithmeticSuccess("PASS", "/", a, b, result, cref);
			}
			if (nrOfFailedTests > 24) return nrOfFailedTests;
		}
		//		if (i % 1024 == 0) std::cout << '.';
	}
	cout << "Total State Space: " << setw(10) << NR_VALUES * NR_VALUES << " Overflows: " << setw(10) << nrOfOverflows << " Underflows " << setw(10) << nrOfUnderflows << endl;
	return nrOfFailedTests;
}

template<size_t nbits, typename BlockType = uint8_t>
void TestMostSignificantBit() {
	using namespace std;
	using namespace sw::unum;
	blockbinary<nbits, BlockType> a;
	cout << to_binary(a) << ' ' << a.msb() << endl;
	a = 1;
	for (size_t i = 0; i < nbits; ++i) {
		cout << to_binary(a) << ' ' << a.msb() << endl;
		a <<= 1;
	}
}

// generate specific test case that you can trace with the trace conditions in blockbinary
// for most bugs they are traceable with _trace_conversion and _trace_add
template<size_t nbits, typename StorageBlockType = uint8_t>
void GenerateTestCase(int64_t lhs, int64_t rhs) {
	using namespace sw::unum;
	blockbinary<nbits, StorageBlockType> a, b, result, reference;

	a.set_raw_bits(uint64_t(lhs));
	b.set_raw_bits(uint64_t(rhs));
	result = a / b;

	long long _a, _b, _c;
	_a = (long long)a;
	_b = (long long)b;
	_c = _a / _b;

	std::streamsize oldPrecision = std::cout.precision();
	std::cout << std::setprecision(nbits - 2);
	std::cout << std::setw(nbits) << _a << " / " << std::setw(nbits) << _b << " = " << std::setw(nbits) << _c << std::endl;
	std::cout << to_binary(a) << " / " << to_binary(b) << " = " << to_binary(result) << " (reference: " << _c << ")   " << std::endl;
	//	std::cout << to_hex(a) << " * " << to_hex(b) << " = " << to_hex(result) << " (reference: " << std::hex << ref << ")   ";
	reference.set_raw_bits(_c);
	std::cout << (result == reference ? "PASS" : "FAIL") << std::endl << std::endl;
	std::cout << std::dec << std::setprecision(oldPrecision);
}

// conditional compile flags
#define MANUAL_TESTING 0
#define STRESS_TESTING 0

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	bool bReportIndividualTestCases = true;
	int nrOfFailedTestCases = 0;

	std::string tag = "blockbinary division: ";

#if MANUAL_TESTING

//	TestMostSignificantBit<27, uint8_t>();
//	TestMostSignificantBit<27, uint16_t>();
//	TestMostSignificantBit<33, uint32_t>();

	GenerateTestCase<4>(0x8,0x1);  // -8 / 1 => -8

	nrOfFailedTestCases += ReportTestResult(VerifyDivision<4, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<4>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<8, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<8>", "division");


#if STRESS_TESTING

#endif

#else

	cout << "blockbinary division validation" << endl;

	nrOfFailedTestCases += ReportTestResult(VerifyDivision<4, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<4,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<5, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<5,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<6, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<6,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<7, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<7,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<8, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<8,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<9, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<9,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<10, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<10,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<12, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<12,uint8_t>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyDivision<9, uint16_t>(tag, bReportIndividualTestCases), "blockbinary<9,uint16_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<11, uint16_t>(tag, bReportIndividualTestCases), "blockbinary<11,uint16_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<13, uint16_t>(tag, bReportIndividualTestCases), "blockbinary<13,uint16_t>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyDivision<12, uint32_t>(tag, bReportIndividualTestCases), "blockbinary<12,uint32_t>", "division");

#if STRESS_TESTING

	nrOfFailedTestCases += ReportTestResult(VerifyDivision<16, uint8_t>(tag, bReportIndividualTestCases), "blockbinary<16,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<16, uint16_t>(tag, bReportIndividualTestCases), "blockbinary<16,uint16_t>", "division");


#endif  // STRESS_TESTING

#endif  // MANUAL_TESTING

	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
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
