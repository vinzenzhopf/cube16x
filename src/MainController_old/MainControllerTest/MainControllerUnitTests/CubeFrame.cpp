


#include <sstream>
#include "CubeFrame.h"



CubeFrame::CubeFrame() : 
	_frame_data() {

}

CubeFrame::CubeFrame(std::bitset<CUBE_SIZE> &frame_data) :
	_frame_data(frame_data) {

}

void CubeFrame::set_dot(int plane_idx, int col_idx, int row_idx, bool data) {
	const int idx = plane_idx*CUBE_FRAME_PLANE_SIZE + col_idx * CUBE_FRAME_ROW_SIZE + row_idx;
	_frame_data[idx] = data;
}
void CubeFrame::set_row(int plane_idx, int col_idx, uint16_t data) {
	const int idx = plane_idx*CUBE_FRAME_PLANE_SIZE + col_idx * CUBE_FRAME_ROW_SIZE;
	for (int i = 0; i < 16; i++) {
		const bool tmp = (data & (1 << i)) > 0;
		_frame_data[idx + i] = tmp;
	}
}

//void CubeFrame::set_plane(int plane_idx, uint16_t data[]) {
//
//}

bool CubeFrame::get_dot(int plane_idx, int col_idx, int row_idx) const{
	const int idx = plane_idx*CUBE_FRAME_PLANE_SIZE + col_idx * CUBE_FRAME_ROW_SIZE + row_idx;
	return _frame_data[idx];
}

bool CubeFrame::get_idx(int idx) const{
	return _frame_data[idx];
}

uint16_t CubeFrame::get_row(int plane_idx, int col_idx) const{
	const int idx = plane_idx*CUBE_FRAME_PLANE_SIZE + col_idx * CUBE_FRAME_ROW_SIZE;
	uint16_t val = 0;
	for (int i = 0; i < 16; i++) {
		const uint16_t tmp = _frame_data[idx + i];
		val |= tmp << i;
	}
	return val;
}
//uint16_t[] CubeFrame::get_plane(int plane_idx)
//{
//
//}

bool CubeFrame::is_equal(std::unique_ptr<CubeFrame> other) {
	for (int i = 0; i < CUBE_FRAME_CUBE_SIZE; i++) {
		if (_frame_data[i] != other->get_idx(i))
			return false;
	}
	return true;
}

void CubeFrame::reset() {
	_frame_data.reset();
}

std::string CubeFrame::to_string() const {
	return print_cube();
}

std::string CubeFrame::print_plane(int plane_idx) const {
	std::ostringstream out;
	std::bitset<16> row;
	for (int i = 0; i < CUBE_FRAME_ROW_SIZE; i++) {
		row.reset();
		for (int j = 0; j < CUBE_FRAME_ROW_SIZE; j++) {
			row[j] = get_dot(plane_idx, i, j);
		}
		out << row << '\n';
	}
	return out.str();
}

std::string CubeFrame::print_cube() const {
	std::ostringstream out;
	for (int i = 0; i < CUBE_FRAME_ROW_SIZE; i++) {
		out << "Plane " << i << ":\n";
		out << print_plane(i) << "\n";
	}
	return out.str();
}