module module_a(
    input clock,
    input reset,
    input cnt_en,
    output reg [7:0] data
);

always_ff @(posedge clock) begin
    if (reset) begin
        data <= 8'h00;
    end else if (cnt_en) begin
        data <= data + 1;
    end
end

endmodule
