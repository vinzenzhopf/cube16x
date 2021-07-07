#pragma once

#include <inttypes.h>
#include <bitset>
#include <memory>

constexpr uint8_t CUBE_FRAME_ROW_SIZE = 16;
constexpr uint16_t CUBE_FRAME_PLANE_SIZE = CUBE_FRAME_ROW_SIZE * CUBE_FRAME_ROW_SIZE; //256
constexpr uint16_t CUBE_FRAME_CUBE_SIZE = CUBE_FRAME_PLANE_SIZE * CUBE_FRAME_ROW_SIZE; //4096

class CubeFrame {
public:
	CubeFrame();
	CubeFrame(std::bitset<CUBE_FRAME_CUBE_SIZE> &frame_data);

	void set_dot(int plane_idx, int col_idx, int row_idx, bool data);
	void set_row(int plane_idx, int col_idx, uint16_t data);
	//void set_plane(int plane_idx, uint16_t data[]);

	bool get_dot(int plane_idx, int col_idx, int row_idx) const;
	uint16_t get_row(int plane_idx, int col_idx) const;
	//uint16_t[] get_plane(int plane_idx);
	bool get_idx(int idx) const;

	bool is_equal(std::unique_ptr<CubeFrame> other);

	void reset();

	std::string to_string() const;
	std::string print_plane(int plane_idx) const;
	std::string print_cube() const;

private:
	size_t _current_register;
	std::bitset<CUBE_FRAME_CUBE_SIZE> _frame_data;

	

};