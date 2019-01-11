//  ____         __  __ _       
// |  _ \ _   _ / _|/ _(_)_ __  
// | |_) | | | | |_| |_| | '_  | 
// |  __/| |_| |  _|  _| | | | |
// |_|    \__,_|_| |_| |_|_| |_|          
//
// BSD 3-Clause License

// Copyright (c) 2019, Thomas Gourgues (thomas.gourgues@gmail.com)
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef PFN_URI_MAIN_HPP
#define PFN_URI_MAIN_HPP

#include "uri_parser.hpp"

#include <cstdint>
#include <map>
#include <ostream>
#include <string>

namespace pfn {

template<typename Parser>
struct parser_trait { using type = Parser; };

template<typename Parser>
class basic_uri {
public:
  using parser_type = typename parser_trait<Parser>::type;
  friend typename parser_trait<Parser>::type;

  basic_uri()
    : port_(80)
  {}

  basic_uri(const basic_uri& uri) = default;

  basic_uri(basic_uri&& uri)
    : scheme_(std::move(uri.scheme_)),
      host_(std::move(uri.host_)),
      port_(std::move(uri.port_)),
      path_(std::move(uri.path_)),
      fragment_(std::move(uri.fragment_)),
      query_string_(std::move(uri.query_string_)),
      query_params_(std::move(uri.query_params_))
  {}

  basic_uri(const std::string& url)
    : basic_uri() {
    parse(url);
  }

  basic_uri(const std::string& host, const std::string& path)
    : basic_uri() {
    parse(host + path);
  }

  virtual ~basic_uri() {}

  const std::string& scheme() const { return scheme_; }
  const std::string& host() const { return host_; }

  const std::string path() const {
    return path_.size() > 0 ? path_ : std::string("/");
  }

  const std::string& fragment() const { return fragment_; }
  const std::string& query_string() const { return query_string_; }

  std::string str() const {
    return scheme_ + "://" + host_ +
           (port_ != 80 && port_ != 443 ? ":" + std::to_string(port_) : "") +
           path_ +
           fragment_ +
           (query_string_.size() > 0 ? "?" + query_string_ : "");
  }

protected:
  void parse(const std::string& url) { parser_.parse(*this, url); }

private:
  parser_type parser_;

  std::string scheme_;
  std::string host_;
  uint32_t    port_;
  std::string path_;
  std::string fragment_;
  std::string query_string_;

  std::map<std::string, std::string> query_params_;
};

template <typename P>
inline std::ostream& operator<<(std::ostream& o, const basic_uri<P>& uri) {
  return o << uri.str();
}

using uri = basic_uri<pfn::regex_parser>;

}

#endif // PFN_URI_MAIN_HPP
