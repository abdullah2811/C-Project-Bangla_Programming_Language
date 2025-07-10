লাগাও <সটডিও>
লাগাও <গণিত>

পূর্ণ add(পূর্ণ x, পূর্ণ y) {
    ফেরত x + y;
}

পূর্ণ প্রধান() {
    পূর্ণ a, b, r;

    লেখো("Enter first number: ");
    নাও("%d", &a);

    লেখো("Enter second number: ");
    নাও("%d", &b);

    r = add(a, b);

    যদি (r > 100) {
        লেখো("Result is larger than 100!\n");
    } নাহলে {
        লেখো("Result: %d\n", r);
    }

    জন্য (পূর্ণ i = 0; i < 5; i++) {
        লেখো("i : %d\n", i);
    }

    ফেরত 0;
}
