module module_b(
    input clock,
    input reset,
    output cnt_en
);

reg [1:0] counter;

always_ff @(posedge clock) begin
    if (reset) begin
        counter <= 2'b00;
    end else begin
        counter <= counter + 1;
    end
end

assign cnt_en = (counter == 2'b11);

endmodule
