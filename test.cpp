#include <gtest/gtest.h>
#include "rational.hpp"
#include <sstream>



TEST(DefaultCtor, verifyInitialization) {
	Rational r;
	EXPECT_EQ(r.den(), 1);
	EXPECT_EQ(r.num(), 0);

}

TEST(ValueCtor, verifyValues) {
	Rational r{ 27, 72 };
	EXPECT_EQ(r.num(), 3);
	EXPECT_EQ(r.den(), 8);
}

TEST(Setters, verifySetNumerator) {
	Rational r;
	r.num(4);
	EXPECT_EQ(r.num(), 4);
	EXPECT_EQ(r.den(), 1);
}

TEST(Setters, verifySetDenominator) {
	Rational r;
	r.den(12);
	EXPECT_EQ(r.num(), 0);
	EXPECT_EQ(r.den(), 1);
	r.num(4);
	r.den(-8);
	EXPECT_EQ(r.num(), -1);
	EXPECT_EQ(r.den(), 2);
	EXPECT_THROW(r.den(0), std::domain_error);
}

TEST(MathOps, verifyMultiplication) {
	Rational r{ 3, 4 };
	Rational q{ 5, 6 };
	Rational p;
	p = q * r;
	EXPECT_EQ(p.num(), 5);
	EXPECT_EQ(p.den(), 8);
	p = q + r;
	EXPECT_EQ(p.num(), 19);
	EXPECT_EQ(p.den(), 12);
}

TEST(MathOps, verifyAddition) {
	Rational r{ 3, 4 };
	Rational q1{ 5, 6 };
	Rational p1;
	p1 = r + q1;
	EXPECT_EQ(p1.num(), 19);
	EXPECT_EQ(p1.den(), 12);

}
TEST(MathOps, verifySubtraction) {
	Rational r{ 5, 6 };
	Rational p{ 2, 6 };
	Rational a;
	a = r - p;
	EXPECT_EQ(a.num(), 1);
	EXPECT_EQ(a.den(), 2);
	Rational b{ 2, 5 };
	Rational c{ 3, 12 };
	Rational d;
	d = b - c;
	EXPECT_EQ(d.num(), 3);
	EXPECT_EQ(d.den(), 20);
}

TEST(MathOps, verifyMinus) {
	Rational r{ 3, 4 };
	Rational p;
	p = -r;
	EXPECT_EQ(p.num(), -3);
	EXPECT_EQ(p.den(), 4);
}

TEST(MathAssignOps, verifyPlusEquals) {
	Rational r{ 1, 4 };
	Rational q{ 1, 3 };
	r += q;
	EXPECT_EQ(r.num(), 7);
	EXPECT_EQ(r.den(), 12);

}

TEST(MathAssignOps, verifyDivisionByZeroError) {
	Rational r{ 3, 4 };
	Rational q{ 5, 6 };
	Rational p;
	EXPECT_THROW(p = q / (r - r), std::domain_error);
}
TEST(MathAssignOps, verifyTimesEquals) {
	Rational r{ 1, 4 };
	Rational q{ 1, 3 };
	r *= q;
	EXPECT_EQ(r.num(), 1);
	EXPECT_EQ(r.den(), 12);

}
TEST(MathAssignOps, verifyMinusEquals) {
	Rational r{ 10, 12 };
	Rational q{ 3, 12 };
	r -= q;
	EXPECT_EQ(r.num(), 7);
	EXPECT_EQ(r.den(), 12);

}

TEST(MathAssignOps, verifyIncrementPlus) {
	Rational r{ 1, 6 };
	++r;
	EXPECT_EQ(r.num(), 7);
	EXPECT_EQ(r.den(), 6);
	r++;
	EXPECT_EQ(r.num(), 13);
	EXPECT_EQ(r.den(), 6);
}

TEST(MathAssignOps, verifyDecrementMinus) {
	Rational r{ 13, 6 };
	--r;
	EXPECT_EQ(r.num(), 7);
	EXPECT_EQ(r.den(), 6);
	r--;
	EXPECT_EQ(r.num(), 1);
	EXPECT_EQ(r.den(), 6);
}

TEST(CompareOp, verifyEquals) {
	Rational r{ 1, 2 };
	Rational q{ 2, 5 };
	bool b;
	b = r == q;
	EXPECT_FALSE(b);
	r.num(0);
	q.num(0);
	b = r == q;
	EXPECT_TRUE(b);
}

TEST(CompareOps, verifyGreaterThanLessThan) {
	Rational r{ 1, 2 };
	Rational q{ 2, 5 };
	bool b;
	b = r > q;
	EXPECT_TRUE(b);
	b = r < q;
	EXPECT_FALSE(b);
}

TEST(CompareOps, verifyGreaterThanEqualsLessThanEquals) {
	Rational r{ 1, 2 };
	Rational q{ 2, 4 };
	bool b;
	b = r >= q;
	EXPECT_TRUE(b);
	b = r <= q;
	EXPECT_TRUE(b);
	r.den(20);
	b = r <= q;
	EXPECT_TRUE(b);
	b = r >= q;
	EXPECT_FALSE(b);
}

TEST(ConvertOps, verifyImplicitFromInt) {
	Rational r = 5;
	EXPECT_EQ(r.num(), 5);
	EXPECT_EQ(r.den(), 1);
	double d = r;
	EXPECT_EQ(d, 5.0);

}

TEST(ConvertOps, verifyImplicitFromDouble) {
	Rational r = 5;
	double d = r;
	EXPECT_EQ(d, 5.0);
}

TEST(ConvertOps, verifyMathAndComparisonOfIntDouble) {
	Rational r = 5;
	r += 7;
	EXPECT_EQ(r.num(), 12);
	EXPECT_TRUE(r == 12.0);
}

TEST(ConvertOps, verifyExplicitFromDoubleInt) {
	Rational r;
	r = (Rational)3.33333;
	int i = (int)r;
	EXPECT_EQ(r.num(), 333333);
	EXPECT_EQ(r.den(), 100000);
	EXPECT_EQ(i, 3);

}
TEST(IoOps, verifyPrintMethod) {
	Rational r{ 3, 4 };
	std::ostringstream out;
	out << r;
	EXPECT_EQ(out.str(), "3/4");
}