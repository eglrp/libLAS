#ifndef TS2LAS_HPP_INCLUDED

#include <liblas/cstdint.hpp>
#include <liblas/detail/utility.hpp>

#include <liblas/laswriter.hpp>
#include <liblas/laspoint.hpp>
#include <liblas/lascolor.hpp>
#include <iostream>
#ifdef _WIN32
#define compare_no_case(a,b,n)  _strnicmp( (a), (b), (n) )
#else
#define compare_no_case(a,b,n)  strncasecmp( (a), (b), (n) )
#endif

using namespace liblas;

struct ScanRow
{
    ScanRow() :
        Code(0),
        Line(0),
        EchoInt(0),
        x(0),
        y(0),
        z(0)
    {}

    liblas::uint8_t Code;
    liblas::uint8_t Line;
    liblas::uint16_t EchoInt;

    liblas::int32_t x;
    liblas::int32_t y;
    liblas::int32_t z;

};


struct Point3d
{
    Point3d() :
        x(0),
        y(0),
        z(0)
    {}

    liblas::int32_t x;
    liblas::int32_t y;
    liblas::int32_t z;

};

struct ScanPnt
{
    ScanPnt() :
        Code(0),
        Echo(0),
        Flag(0),
        Mark(0),
        Line(0),
        Intensity(0)
    {}

    Point3d Pnt;
    liblas::uint8_t Code;
    liblas::uint8_t Echo;
    liblas::uint8_t Flag;
    liblas::uint8_t Mark;
    liblas::uint16_t Line;
    liblas::uint16_t Intensity;

};


struct ScanHdr
{
    ScanHdr() :
        HdrSize(0),
        HdrVersion(0),
        Tunniste(0),
        PntCnt(0),
        Units(0),
        OrgX(0),
        OrgY(0),
        OrgZ(0),
        Time(0),
        Color(0)
    {}

    liblas::int32_t HdrSize;
    liblas::int32_t HdrVersion;
    liblas::int32_t Tunniste;
    char Magic[4];
    liblas::int32_t PntCnt;
    liblas::int32_t Units;
    double OrgX;
    double OrgY;
    double OrgZ;
    liblas::int32_t Time;
    liblas::int32_t Color;

    // 
    // int HdrSize;
    // int HdrVersion;
    // int Tunniste;
    // char Magic[4];
    // int PntCnt;
    // int Units;
    // double OrgX;
    // double OrgY;
    // double OrgZ;
    // int Time;
    // int Color;
};


namespace liblas { namespace detail {


 
template <>
inline void read_n <ScanRow>(ScanRow& dest, std::istream& src, std::streamsize const& num)
{
    // TODO: Review and redesign errors handling logic if necessary
    if (!src)
        throw std::runtime_error("detail::liblas::read_n<ScanRow> input stream is not readable");

    src.read(detail::as_buffer(dest), num);
    detail::check_stream_state(src);

    // Fix little-endian
    LIBLAS_SWAP_BYTES(dest.x);
    LIBLAS_SWAP_BYTES(dest.y);
    LIBLAS_SWAP_BYTES(dest.z);
    LIBLAS_SWAP_BYTES(dest.Code);
    LIBLAS_SWAP_BYTES(dest.Line);
    LIBLAS_SWAP_BYTES(dest.EchoInt);

}

template <>
inline void read_n <ScanPnt>(ScanPnt& dest, std::istream& src, std::streamsize const& num)
{
    // TODO: Review and redesign errors handling logic if necessary
    if (!src)
        throw std::runtime_error("detail::liblas::read_n<ScanPnt> input stream is not readable");

    src.read(detail::as_buffer(dest), num);
    detail::check_stream_state(src);

    // Fix little-endian
    LIBLAS_SWAP_BYTES(dest.Pnt.x);
    LIBLAS_SWAP_BYTES(dest.Pnt.y);
    LIBLAS_SWAP_BYTES(dest.Pnt.z);
    LIBLAS_SWAP_BYTES(dest.Code);
    LIBLAS_SWAP_BYTES(dest.Echo);
    LIBLAS_SWAP_BYTES(dest.Flag);
    LIBLAS_SWAP_BYTES(dest.Mark);
    LIBLAS_SWAP_BYTES(dest.Line);
    LIBLAS_SWAP_BYTES(dest.Intensity);

}

template <>
inline void read_n <ScanHdr>(ScanHdr& dest, std::istream& src, std::streamsize const& num)
{
    // TODO: Review and redesign errors handling logic if necessary
    if (!src)
        throw std::runtime_error("detail::liblas::read_n<ScanHdr> input stream is not readable");

    src.read(detail::as_buffer(dest), num);
    detail::check_stream_state(src);

    // Fix little-endian
    LIBLAS_SWAP_BYTES(dest.HdrSize);
    LIBLAS_SWAP_BYTES(dest.HdrVersion);
    LIBLAS_SWAP_BYTES(dest.Tunniste);
    LIBLAS_SWAP_BYTES(dest.Magic);
    LIBLAS_SWAP_BYTES(dest.PntCnt);
    LIBLAS_SWAP_BYTES(dest.Units);
    LIBLAS_SWAP_BYTES(dest.Time);
    LIBLAS_SWAP_BYTES(dest.Color);

}
}} // namespace liblas::detail

#endif // TS2LAS_HPP_INCLUDED
